function adjustLine(line) {
  var words = line.split(" ");
}

function formatParagraph(paragraph) {
  var words = paragraph.split(" ");

  console.log(words);

  var res = '';
  var line = '';

  for (var i = 0; i < words.length; i++) {
    if (words[i].length > 0) {
      if (line.length + 1 + words[i].length > 80) {
        res += line + '\n';
        line = words[i];
      } else {
        if (line.length > 0) {
          line += ' ';
        }
        line += words[i];
      }
    }
  }

  res += line + '\n';

  return res;
}

$('#format').click(function() {
  var text = $('textarea').val();
  console.log(text);

  var lines = text.split('\n');

  console.log(lines.length);

  var result = '';
  var paragraph = '';
  for (var i = 0; i < lines.length; i++) {
    trimmed = $.trim(lines[i]);

    if (trimmed.length > 0) {
      if (paragraph.length > 0) {
        paragraph += ' ';
      }
      paragraph += trimmed;
    } else {
      if (paragraph.length > 0) {
        formatted_paragraph =  formatParagraph(paragraph);
        console.log(formatted_paragraph);

        result += formatted_paragraph;
      }
      paragraph = '';

      result += '\n';
    }
  }

  $('textarea').val(result);
});
