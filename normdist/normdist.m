counts = zeros(101,1);

all_sums = [];

N = 20000

for n = 1:N
  a = rand(100,1) > 0.5;
  s = sum(a);
  counts(s + 1) += 1;
  all_sums = [ all_sums s ];
endfor

printf("min = %f, max = %f, mean = %f\n", min(all_sums), max(all_sums), mean(all_sums))
printf("stddev = %f\n", std(all_sums))

m = mean(all_sums);
stddev = std(all_sums);
for std_mult = 1:3
  in_range = (all_sums > m - stddev * std_mult) & (all_sums < m + stddev * std_mult);
  in_range = in_range .+ 0.0;
  printf("Percentage of values withing %d std devs = %0.2f\n", std_mult, sum(in_range) / N * 100.);
endfor

% plot(counts);
