var overlay = document.querySelector('.overlay');

var dataset = [];

var in_settings = false;
var settings_first_open = true;

function addSavedShortcut(shortcut, url) {
  var templ = $('#saved-shortcut-template');
  var instance = $(templ).clone();
  $(instance).attr('id', 'saved-' + shortcut);
  $(instance).find('.shortcut-name').text(shortcut);
  $(instance).find('.shortcut-url').text(url);
  $(instance).show();
  $('#saved-shortcuts-body').prepend(instance);
}

function openSettings(event) {
  $('#search-box').hide();
  $('#settings-menu').show();
  in_settings = true;

  chrome.storage.sync.get(function(stored) {
    console.log('Stored:', stored);
    for (key in stored) {
      console.log(key, ' -> ', stored[key]);

      addSavedShortcut(key, stored[key]);
    }
  });

  if (settings_first_open) {
    settings_first_open = false;

    $('#clean-storage').click(function(event) {
      chrome.storage.sync.clear(function () {
        console.log("Clear done", arguments);
      });
    });

    $('#link-add').click(function(ev) {
      var name = $('#link-name').val();
      var url = $('#link-url').val();

      if (name && name.length > 0) {
        chrome.storage.sync.set({'petko': 'minkov'});
        var to_store = {}
        to_store[name] = url;
        chrome.storage.sync.set(to_store, function(args) {
          console.log('Saved: ', name, ' ', url);
          console.log(arguments);
          console.log(args);

          addSavedShortcut(name, url);
        });
      }
    });
  }
}

$(document).ready(function() {
  $('#ta-inp').focus();
  $('.settings').click(openSettings);

  chrome.storage.sync.get(function(shortcuts) {
    if (false == $.isEmptyObject(shortcuts)) {
      for (var key in shortcuts) {
        dataset.push({
          key: key,
          value: shortcuts[key]
        });
      }
      console.log(dataset);
    }
  });
});

$(document).keyup(function(e) {
  if (e.which == 27) {
    if (in_settings) {
      // TODO(petko): Add a close button as well.
      in_settings = false;
      $('#settings-menu').hide();
      $('#search-box').show();
    } else {
      chrome.runtime.sendMessage('hide_popup');
    }
  }
});

overlay.addEventListener('click', function() {
  chrome.runtime.sendMessage('hide_popup');
});

var substringMatcher = function(strs) {
  return function findMatches(q, cb) {
    var matches, substringRegex;

    // an array that will be populated with substring matches
    matches = [];

    // regex used to determine if a string contains the substring `q`
    substrRegex = new RegExp(q, 'i');

    // iterate through the pool of strings and for any string that
    // contains the substring `q`, add it to the `matches` array
    $.each(dataset, function(i, entry) {
      if (substrRegex.test(entry.key)) {
        matches.push(entry);
      }
    });
    /*
    $.each(strs, function(i, str) {
      if (substrRegex.test(str)) {
        matches.push(str);
      }
    });
    */

    cb(matches);
  };
};

var states = ['Alabama', 'Alaska', 'Arizona', 'Arkansas', 'California',
  'Colorado', 'Connecticut', 'Delaware', 'Florida', 'Georgia', 'Hawaii',
  'Idaho', 'Illinois', 'Indiana', 'Iowa', 'Kansas', 'Kentucky', 'Louisiana',
  'Maine', 'Maryland', 'Massachusetts', 'Michigan', 'Minnesota',
  'Mississippi', 'Missouri', 'Montana', 'Nebraska', 'Nevada', 'New Hampshire',
  'New Jersey', 'New Mexico', 'New York', 'North Carolina', 'North Dakota',
  'Ohio', 'Oklahoma', 'Oregon', 'Pennsylvania', 'Rhode Island',
  'South Carolina', 'South Dakota', 'Tennessee', 'Texas', 'Utah', 'Vermont',
  'Virginia', 'Washington', 'West Virginia', 'Wisconsin', 'Wyoming'
];

function render_result(result) {
  return '<div>'+ result.key + '<div class="res_url">' + result.value + '</div></div>';
};

function display(result) {
  return result.key;
}

var box = $('#ta-inp');
box.typeahead({
  hint: true,
  highlight: true,
  minLength: 1
},
{
  name: 'states',
  source: substringMatcher(states),
  display: display,
  templates: {
    suggestion: render_result
  }
});

box.bind('typeahead:select', function(ev, shortcut) {
  var redirect_url = shortcut.value;
  console.log('Redirecting to ', redirect_url);

  chrome.runtime.sendMessage({target: redirect_url});
});
