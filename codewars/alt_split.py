class Node(object):
    def __init__(self, data=None):
        self.data = data
        self.next = None
    
class Context(object):
    def __init__(self, first, second):
        self.first = first
        self.second = second


def build_list(ar):
  n = Node(ar[0])
  fi = n
  for i in range(1, len(ar)):
    n.next = Node(ar[i])
    n = n.next

  return fi

    
    
def alternating_split(head):
  nl = head.next

  fi = []
  se = []

  while head:
    if head:
      fi.append(head.data)
    if head.next:
      se.append(head.next.data)

    head = head.next
    if head:
      head = head.next

  return Context(build_list(fi), build_list(se))

    
li = build_list([1, 2, 3, 4, 5])

alternating_split(li)
