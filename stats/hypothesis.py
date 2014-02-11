from stats import *

def hypothesis_test(original_mean, original_stddev, n_samples, new_mean):
  """
  See this video:
  https://www.khanacademy.org/math/probability/statistics-inferential/hypothesis-testing/v/hypothesis-testing-and-p-values
  """

  sample_mean_stddev = original_stddev / math.sqrt(n_samples)
  print "Stddev of the sample mean", sample_mean_stddev

  z_score = (original_mean - new_mean) / sample_mean_stddev

  print "Z-score =", z_score

  return -1.96 < z_score and z_score < 1.96
  

if __name__ == '__main__':
  res = hypothesis_test(1.2, 0.5, 100, 1.05)
  print "Null hypothesis is", res
