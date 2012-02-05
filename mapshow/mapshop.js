var map_;
var service_;
var infowindow_;
var lastBounds_;
var markers_ = [];
var selectedType_;
var selectedElem_;

var EVENT_click = 'click';

var beginBarrierCount = 2;


var types = ['restaurant', 'art_gallery', 'bakery', 'atm', 'bank', 'bar',
 'bicycle_store', 'book_store', 'cafe', 'car_wash', 'clothing_store',
 'convenience_store', 'department_store', 'electronics_store', 'finance',
 'fire_station', 'food', 'gas_station', 'grocery_or_supermarket', 'gym',
 'hair_care', 'health', 'home_goods_store', 'library', 'meal_takeaway',
 'movie_rental', 'movie_theater', 'night_club', 'parking', 'airport',
 'school', 'shoe_store', 'shopping_mall', 'store'];


/* Non-floodable op. */
function DelayedOp(timeoutSeconds) {
  this.timeoutMs_ = timeoutSeconds * 1000;
  this.timeout_ = null;
  this.blocked_ = false;
};
DelayedOp.count = 0;
DelayedOp.prototype.execute = function(callback) {
  if (this.blocked_) {
    return;
  }
  console.log('execute' + DelayedOp.count++);
  if (this.timeout_) {
    clearTimeout(this.timeout_);
  }
  this.timeout_ = setTimeout(function() {
    callback();
  }, this.timeoutMs_);
};
DelayedOp.prototype.block = function() {
  this.blocked_ = true;
};
DelayedOp.prototype.unblock = function() {
  this.blocked_ = false;
}

var searchOp_ = new DelayedOp(1);


function maps_init() {
  if (--beginBarrierCount == 0)
    startApp();
}

$(document).ready(function() {
  if (--beginBarrierCount == 0)
    startApp();
});


function addressToLatLngBounds(address, callback) {
  var request = {};
  request.address = address;

  var geocoder = new google.maps.Geocoder();
  geocoder.geocode(request, function(results, status) {
    if (status == 'OK' && results && results.length > 0) {
      var first = results[0];
      var bounds = first.geometry.bounds;
      callback(bounds);
    } else {
      callback(null);
    }
  });
}

function startApp() {
  startAppWithBounds(null);
}

// "hello_world" -> "Hello world".
function normType(typeName) {
  typeName = typeName.replace(/_/g, ' ');
  var f = typeName.substr(0, 1);
  typeName = f.toUpperCase() + typeName.substr(1);
  return typeName;
}

function setupNav() {
  for (var i = 0; i < types.length; i++) {
    var norm = normType(types[i]);
    $('#options').append(' <div class=option id=op' + i + ' >' + norm + '</div>');

    $('#op' + i).click(i, function(e) {
      var type = types[e.data];
      selectedType_ = type;
      doSearchLibrary(type);

      $(e.target).addClass('selected_option');
      if (selectedElem_) {
        $(selectedElem_).removeClass('selected_option');
      }
      selectedElem_ = e.target;
    });
  }
}

function startAppWithBounds(opt_bounds) {
  var span=0.1;
  var lat = 37.708;
  var lng = -122.518;
  var bounds = opt_bounds || (new google.maps.LatLngBounds(
    new google.maps.LatLng(lat, lng),
    new google.maps.LatLng(lat + span, lng + span)));

  setupNav();
  setupGoogleMap(bounds);
  setupService();

  $('#type').change(function(e) {
    var selectedType = $(this).find('option:selected').text();
    doSearchLibrary(selectedType);
  });

  google.maps.event.addListener(map_, 'bounds_changed', function() {
    if (!lastBounds_ || !lastBounds_.equals(map_.getBounds())) {
      searchOp_.execute(function() {
        console.log('search!');
        doSearchLibrary(selectedType_ || 'bar');
      });
    }
    lastBounds_ = map_.getBounds();
  });
}

function setupService() {
  service_ = new google.maps.places.PlacesService(map_);
}

function clearResults() {
  for (var i = 0; i < markers_.length; i++) {
    markers_[i].setMap(null);
  }
  markers_ = [];
  searchOp_.unblock();
  $('#results').empty();
}

function doSearchLibrary(type) {
  var request = {};
  request.types = [type];
  request.bounds = map_.getBounds();
  service_.search(request, function(results, status) {
    var S = google.maps.places.PlacesServiceStatus;
    if (status == S.OK) {
      clearResults();
      console.log('search is ok');
      for (var i = 0; i < results.length; i++) { 
        var place = results[i];
	createMarker(place);

      }
      $('#status').text(type + ' :: ' + results.length + ' results found');
    } else if (status == S.ZERO_RESULTS) {
      $('#status').text('No results for type ' + type);
      clearResults();
    }
  });
}

function openIW(place, marker) {
  infowindow_.setContent(place.name);
  infowindow_.open(map_, marker);
  // iw changes bounds, don't trigger search because it annoys.
  searchOp_.block();
}

function createMarker(place) {


  // map marker.
  var placeLoc = place.geometry.location;
  var marker = new google.maps.Marker({
    map: map_,
    position: new google.maps.LatLng(placeLoc.lat(), placeLoc.lng())
  });
  
  google.maps.event.addListener(marker, 'click', function() {
    openIW(place, marker);
  });


  // panel
  var result = $('<div class="result">' + place.name + '</div>');
  $('#results').append(result);
  result.click([place, marker], function(e) {
    openIW(e.data[0], e.data[1]);
  });

  markers_.push(marker);
}


function setupGoogleMap(initialMapBounds) {
  var mapTypeControlOptions = {};
  mapTypeControlOptions.position = google.maps.ControlPosition.LEFT_BOTTOM;

  var zoomControlOptions = {};
  zoomControlOptions.style = google.maps.ZoomControlStyle.SMALL;
  zoomControlOptions.position = google.maps.ControlPosition.LEFT_TOP;

  var myOptions = {
    zoom: 8,
    mapTypeId: google.maps.MapTypeId.ROADMAP,
    mapTypeControlOptions: mapTypeControlOptions,
    zoomControlOptions: zoomControlOptions,
    panControl: false,
    keyboardShortcuts: false
  }
  map_ = new google.maps.Map(document.getElementById('map_holder'), myOptions);
  map_.fitBounds(initialMapBounds);

  infowindow_ = new google.maps.InfoWindow();
  google.maps.event.addListener(infowindow_, 'closeclick', function() {
    searchOp_.unblock();
  });
}


