var map_;

var EVENT_click = 'click';

var beginBarrierCount = 2;

function maps_init() {
  if (--beginBarrierCount == 0)
    startApp();
}

$(document).ready(function() {
  if (--beginBarrierCount == 0)
    startApp();
});

function startApp() {
  startAppWithBounds(null);
}

function startAppWithBounds(opt_bounds) {
  var span = 0.1;
  var lat = 37.708;
  var lng = -122.518;
  var bounds = opt_bounds || (new google.maps.LatLngBounds(
    new google.maps.LatLng(lat, lng),
    new google.maps.LatLng(lat + span, lng + span)));

  setupGoogleMap(bounds);

  $('#btnShow').click(displayMarkers);
}

function displayMarkers() {
  var data = $('#markers').val();
  var coords = data.split(';');
  $.each(coords, function(index, value) {
  });
  // 37.755244,-122.462196
  var lat = 37.755244;
  var lng = -122.462196;
  var marker = new google.maps.Marker({
    map: map_,
    position: new google.maps.LatLng(lat, lng)
  });
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


