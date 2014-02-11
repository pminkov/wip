import stats as s

def linear_regression(x, y):
  """
  See: https://www.khanacademy.org/math/probability/regression/regression-correlation/v/regression-line-example
  """
  xy_mean = s.xy_mean(x, y)
  print xy_mean
  x_mean = s.mean(x)
  y_mean = s.mean(y)
  x_squared_mean = s.mean([xi ** 2 for xi in x])

  # Slope.
  a = (x_mean * y_mean - xy_mean) / (x_mean ** 2 - x_squared_mean)
  # Intercept.
  b = y_mean - a * x_mean

  return (a, b)


if __name__ == '__main__':
  x = [1, 2, 4]
  y = [2, 1, 3]

  print linear_regression(x, y)
  
