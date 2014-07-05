

def fib(a: Int, b: Int): Int = {
  val c = a + b
  if (c >= 4000000) {
    0
  } else {
    val s = if (c % 2 == 0) c else 0
    s + fib(b, c)
  }
}

val ans = fib(1, 1)
println(ans)

