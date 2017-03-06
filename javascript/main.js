function produceMagicNumber(callback) {
  var waitTime = Math.random() * 1000;

  setTimeout(function() {
    console.log('Producing magic number.');
    callback(333);
  }, waitTime);
}


function Once(func) {
  this.func = func;
  this.called = false;
  this.args = null;
};

Once.prototype.run = function(callback) {
  var me = this;
  this.func(function() {
    this.args = arguments;
    callback(arguments);
  });
}

function printMagicNumber() {
  mn.run(function(number) {
    console.log('The number is', number);
  });
}

$(document).ready(function() {
  var mn = new Once(produceMagicNumber);
  printMagicNumber(mn);
  printMagicNumber(mn);
  printMagicNumber(mn);
});

