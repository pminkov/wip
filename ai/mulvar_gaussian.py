
x = (
  (3, 8),
  (4, 7),
  (5, 5),
  (6, 3),
  (7, 2)
)

M = len(x)

# Compute mu
mu = [0.0, 0.0]

for px in x:
  mu[0] += px[0]
  mu[1] += px[1]

mu[0] /= M
mu[1] /= M

print mu

# Compute Sigma
sum = 0.0

sigma = []
sigma.append([0, 0])
sigma.append([0, 0])

for px in x:
  d = [0] * 2
  d[0] = px[0] - mu[0]
  d[1] = px[1] - mu[1]
  sigma[0][0] += d[0] * d[0]
  sigma[0][1] += d[1] * d[0]
  sigma[1][0] += d[0] * d[1]
  sigma[1][1] += d[1] * d[1]

for y in range(2):
  for x in range(2):
    sigma[y][x] /= M

print sigma

  


