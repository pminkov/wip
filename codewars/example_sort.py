import test

def example_sort(arr, example):
  key_to_priority = dict(zip(example, range(len(example))))
  arr.sort(key=lambda val: key_to_priority[val])
  return arr


test.assert_equals(example_sort([1,2,3,4,5],[2,3,4,1,5]),[2,3,4,1,5])

test.assert_equals(example_sort([1,2,3,3,3,4,5],[2,3,4,1,5]),[2,3,3,3,4,1,5])

test.assert_equals(example_sort([1,2,3,3,3,5],[2,3,4,1,5]),[2,3,3,3,1,5])

test.assert_equals(example_sort([1,2,3,3,3,5],
[3,4,5,6,9,11,12,13,1,7,8,2,10]),[3,3,3,5,1,2])

test.assert_equals(example_sort(["a","a","b","f","d","a"],
["c","a","d","b","e","f"]),["a","a","a","d","b","f"])

test.assert_equals(example_sort(["Alice","Bryan","Chad","Darrell",
  "Ellie","Fiona"],["Alice","Bryan","Chad","Darrell","Ellie","Fiona"])
  ,["Alice","Bryan","Chad","Darrell","Ellie","Fiona"])
