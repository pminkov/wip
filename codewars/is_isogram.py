import test

def is_isogram(string):
  return len(set(string.lower())) == len(string)

test.assert_equals(is_isogram("Dermatoglyphics"), True )
test.assert_equals(is_isogram("isogram"), True )
test.assert_equals(is_isogram("aba"), False, "same chars may not be adjacent" )
test.assert_equals(is_isogram("moOse"), False, "same chars may not be same case" )
test.assert_equals(is_isogram("isIsogram"), False )
test.assert_equals(is_isogram(""), True, "an empty string is a valid isogram" )
