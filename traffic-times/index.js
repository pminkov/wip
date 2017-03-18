function initMap() {
  var map;
  /*
  if (navigator && navigator.geolocation) {
    navigator.geolocation.getCurrentPosition(function (position) {
      map = new google.maps.Map(document.getElementById('map'), {
        zoom: 7,
        center: {lat: position.coords.latitude, lng: position.coords.longiture}
      });

      initApp(map);
    });

  } else 
  */
  {
    map = new google.maps.Map(document.getElementById('map'), {
      zoom: 11,
      center: { lat: 37.779236, lng: -122.449621 }
    });

    initApp(map);
  }
}

function initApp(map) {
  var directionsDisplay = new google.maps.DirectionsRenderer;
  var directionsService = new google.maps.DirectionsService;

  directionsDisplay.setMap(map);
  //directionsDisplay.setPanel(document.getElementById('right-panel'));

  var control = document.getElementById('floating-panel');
  control.style.display = 'block';
  map.controls[google.maps.ControlPosition.TOP_CENTER].push(control);

  initTable();

  var onGoClick = function() {
    runAnalysis(directionsService, directionsDisplay);
  }

  //calculateAndDisplayRoute(directionsService, directionsDisplay, false);
  
  document.getElementById('go').addEventListener('click', onGoClick);
  //document.getElementById('end').addEventListener('change', onChangeHandler);
}

function initTable() {
  for (var t = 0; t < 24; t++) {
    $('#times').append(
      '<tr id="time-' + t + '">' + 
        '<td class="used_time">' + t + '</td>' +
        '<td class="time_slot slot_week"></td>' + 
        '<td class="time_slot slot_weekend"></td>' + 
      '</tr>');
  }
}

function ThrottledBatch()  {
  var per_second = 2;
  this.wait_time = 1.0 / per_second * 1000.0;
  this.batch = [];
  this.done = [];
}

ThrottledBatch.prototype.addRequest = function(func) {
  this.batch.push(func);
  this.done.push(false);
}

ThrottledBatch.prototype.executeOne = function(index) {
  var me = this;

  if (index == me.batch.length) {
    return;
  } else {
    
    this.batch[index](function(status) {
      console.log(index, ' -> ', status);
      var timeout;
      if (status == 'OK') {
        setTimeout(function() {
          me.executeOne(index + 1);
        }, me.wait_time);
      } else {
        console.log('Oops, waiting..');
        setTimeout(function() {
          me.executeOne(index);
        }, 1000);
      }
    });
  }
}

ThrottledBatch.prototype.execute = function() {
  console.log('Executing', this.batch.length, 'requests');

  this.executeOne(0);
}

function runAnalysis(directionsService, directionsDisplay) {
  var start = $('#address-from').val();
  var end = $('#address-to').val();

  var batch = new ThrottledBatch();

  var modes = ['Week', 'Weekend'];

  var is_displayed = false;

  hour_lim = 6;

  for (var hour = 0; hour < hour_lim; hour++) {
    $('#time-' + hour + ' .slot_week').text('');
    $('#time-' + hour + ' .slot_weekend').text('');
  }

  for (var mode_i = 0; mode_i < modes.length; mode_i++) {
    mode = modes[mode_i];

    for (var hour = 0; hour < hour_lim; hour++) {
      var d = new Date();
      var adjust = 0;
      if (mode == 'Week') {
        // Wed. -(3 - 1) = -2.
        adjust = -(d.getDay() - 1);
      } else {
        // Wed. (6-3) = 3;
        adjust = 6 - d.getDay()
      }
      d.setDate(d.getDate() + 7 + adjust);

      if (mode == 'Week') {
        console.assert(d.getDay() == 1);
      } else {
        console.assert(d.getDay() == 6);
      }


      d.setHours(hour);

      var params = {
        origin: start,
        destination: end,
        travelMode: 'DRIVING',
        drivingOptions: {
          departureTime: d
        }
      };

      var myParams = {
        hour: hour,
        mode: mode
      }

      batch.addRequest(function(params, myParams, done_callback) {
        directionsService.route(params, function(myParams, response, status) {
          if (status === 'OK') {
            if (response.routes.length > 0) {
              var route = response.routes[0];
              var leg = route.legs[0];
            }

            var selector = ' .slot_week';
            if (myParams.mode == 'Weekend') {
              selector = ' .slot_weekend';
            }

            $('#time-' + myParams.hour + selector).text(leg.duration_in_traffic.text);

            if (!is_displayed) {
              is_displayed = true;
              directionsDisplay.setDirections(response);
            }
          }

          done_callback(status);

        }.bind(this, myParams));
      }.bind(this, params, myParams));
    }
  }

  batch.execute();
}

function calculateAndDisplayRoute(directionsService, directionsDisplay, getTime) {
  var start = "1858 Tacome Ave, Berkeley, CA";
  //var end = "1650 Broadway, Oakland, CA";
  var end = "2 Townsend St, San Francisco, CA";


  var params = {
    origin: start,
    destination: end,
    travelMode: 'DRIVING'
  }

  if (getTime) {
    var hour = document.getElementById('arrive-by').value;

    var d = new Date();
    d.setDate(d.getDate() + 7);
    d.setHours(hour);

    console.log(d);

    var drivingOptions = {
      'departureTime': d
    };

    params['drivingOptions'] = drivingOptions;
  }

  console.log(params);


  directionsService.route(params, function(response, status) {
    if (status === 'OK') {
      console.log(response);
      directionsDisplay.setDirections(response);
    } else {
      window.alert('Directions request failed due to ' + status);
    }
  });
}

