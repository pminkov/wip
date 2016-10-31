"""
Here we're testing the hypothesis:

"The stock market is usually at its highest point".

"""
import pandas

if __name__ == '__main__':
  tables = pandas.read_html('http://www.multpl.com/s-p-500-historical-prices/table/by-month', header=0)
  assert len(tables) == 1
  table = tables[0]
  table.columns = ['Date', 'Price']

  first = True 
  min_future_price = None

  at_top = 0
  not_at_top = 0
  points = 0
  for (idx, row) in table.iterrows():
    date = row['Date']
    year = int(date[-4:])
    assert 1800 < year and year < 2100

    if year < 1960:
      break

    points += 1
    price = row['Price']

    if first:
      min_future_price = price
      first = False
    else:
      if price * 0.8 > min_future_price:
        # If current price falls by 20%, it will still be higher than a future price.
        not_at_top += 1
      else:
        at_top += 1

      if price < min_future_price:
        min_future_price = price


  print 'Total number of price points:', points
  pct = 100.0 * at_top / points
  print 'Number of times the market has been at its highest: %d (%.2f%%)' % (at_top, pct)
  print 'Number of times the marker has not been at its highest: %d (%.2f%%)' % (not_at_top, 100.0 - pct)

        



  
  
