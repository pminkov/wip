def sum(a: String, b: String): String = {
  val aa = a.reverse
  val bb = b.reverse

  val sb = new StringBuilder

  def extractDigit(s: String, pos: Int): Option[Int] = {
    if (pos < s.size) Some(s(pos) - '0') else None
  }

  def runSum(pos: Int, carry: Int): Unit = {
    val digit_a = extractDigit(aa, pos)
    val digit_b = extractDigit(bb, pos)

    val d = (digit_a.getOrElse(0) + digit_b.getOrElse(0) + carry)

    val foundDigit = digit_a.isDefined || digit_b.isDefined

    if (foundDigit || d > 0) {
      val c: Char = ('0' + (d % 10)).toChar
      sb.append(c)
    }

    if (foundDigit) {
      runSum(pos + 1, d / 10)
    }
  }

  runSum(0, 0)

  val res = sb.result.reverse
  res
}


// A number of nine digits, which contains all digits from '1' to '9'
def pandigital(s: String): Boolean = {
  s.size == 9 && !s.contains('0') && s.distinct.size == 9
}


def fib(which: Int, a: String, b: String): Unit = {
  if (which < (1 << 20)) {
    val s = sum(a, b)

    val firstPandigital = pandigital(s.take(9))
    val lastPandigital = pandigital(s.drop(s.size - 9))

    if (which % 1000 == 0) println(which)

    if (firstPandigital && lastPandigital) {
      println(which)
      println(s)
      println
    } else {
      fib(which + 1, b, s)
    }
  }
}


fib(3, "1", "1")
