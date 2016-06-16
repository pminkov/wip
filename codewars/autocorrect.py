import test
import re

def autocorrect(input):
  return re.sub(r"\byo(u+)\b|\bu\b", "your sister", input, flags=re.IGNORECASE)

test.assert_equals(autocorrect("u"),"your sister")
test.assert_equals(autocorrect("you"),"your sister")
test.assert_equals(autocorrect("Youuuuu"),"your sister")
test.assert_equals(autocorrect("youtube"),"youtube")
test.assert_equals(autocorrect("hi you are"), "hi your sister are")
test.assert_equals(autocorrect("bayou"), "bayou")
#'I want to film the bayour sister with your sister and put it on youtube' should equal 'I want to film the bayou with your sister and put it on youtube'


