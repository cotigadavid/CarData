from urllib.request import urlopen as uReq
from bs4 import BeautifulSoup as soup

#my_urlBase = "https://www.autovit.ro/autoturisme/volkswagen/polo?search%5Bfilter_enum_generation%5D%5B0%5D=gen-vw-polo-4&search%5Bfilter_enum_generation%5D%5B1%5D=gen-vw-polo-5&search%5Bfilter_enum_generation%5D%5B2%5D=gen-vw-polo-6&search%5Bfilter_enum_fuel_type%5D%5B0%5D=petrol&search%5Bfilter_enum_fuel_type%5D%5B1%5D=petrol-cng&search%5Bfilter_enum_fuel_type%5D%5B2%5D=petrol-lpg&search%5Bfilter_enum_fuel_type%5D%5B3%5D=diesel&search%5Border%5D=filter_float_price%3Aasc"
fout = open("output.txt", "w")
fin = open("D:/CarData/CarData/linkFile.txt", "r")

#my_urlBase = fin.readlines()[0]
my_urlBase = fin.read()

def ProcessList(p_list):
		nr = 1
		for tag in p_list:
			List = tag.div.div.ul.findAll(["li"]);
			if len(List) == 4 :
				lines = [List[0].string, List[1].string, List[2].string, List[3].string]
				for line in lines:
					fout.write(line)
					fout.write(" ")

				price = tag.find(["span"], class_="optimus-app-epvm6 e1b25f6f8")
				fout.write("/")
				fout.write(price.string)
				fout.write('\n')
				nr = nr + 1


uClient = uReq(my_urlBase)
page_html = uClient.read()
uClient.close()
page_soup = soup(page_html, "html.parser")

nrOfPages = 1
pages = page_soup.findAll(["a"], class_="optimus-app-g4wbjr ekxs86z0")
if len(pages) != 0:
	nrOfPages = int(pages[len(pages) - 1].span.string)

my_url = my_urlBase

qMarkLocation = my_urlBase.find("?"); 

pageAddSyntax = "&page="

if qMarkLocation == -1:
	pageAddSyntax = "?" + pageAddSyntax

for i in range(1, nrOfPages + 1):

	if (i != 1):
		my_url = my_urlBase + pageAddSyntax + str(i);

	uClient = uReq(my_url)
	page_html = uClient.read()
	uClient.close()
	page_soup = soup(page_html, "html.parser")

	tags1 = page_soup.findAll(["article"], class_="optimus-app-10uqxf9 e1b25f6f16")
	tags2 = page_soup.findAll(["article"], class_="optimus-app-y42k2g e1b25f6f16")

	ProcessList(tags1)
	ProcessList(tags2)

	print(i)

fin.close()
fout.close()

#https://www.autovit.ro/autoturisme/volkswagen/polo/de-la-2007?search%5Bfilter_enum_fuel_type%5D=petrol&search%5Bfilter_float_mileage%3Ato%5D=170000&search%5Bfilter_enum_generation%5D=gen-vw-polo-5&search%5Bfilter_float_price%3Afrom%5D=3000&search%5Bfilter_float_price%3Ato%5D=10000&search%5Bfilter_float_year%3Ato%5D=2021&search%5Bfilter_float_mileage%3Afrom%5D=5000&search%5Border%5D=filter_float_price%3Aasc
#https://www.autovit.ro/autoturisme/volkswagen/polo/de-la-2001?search%5Bfilter_enum_fuel_type%5D=petrol&search%5Bfilter_float_mileage%3Ato%5D=270000&search%5Bfilter_enum_generation%5D%5B0%5D=gen-vw-polo-4&search%5Bfilter_enum_generation%5D%5B1%5D=gen-vw-polo-5&search%5Bfilter_float_price%3Afrom%5D=100&search%5Bfilter_float_price%3Ato%5D=20000&search%5Bfilter_float_year%3Ato%5D=2021&search%5Bfilter_float_mileage%3Afrom%5D=1000&search%5Border%5D=filter_float_price%3Aasc
#https://www.autovit.ro/autoturisme/volkswagen/polo/de-la-2001?search%5Bfilter_enum_fuel_type%5D=petrol&search%5Bfilter_float_mileage%3Ato%5D=270000&search%5Bfilter_enum_generation%5D%5B0%5D=gen-vw-polo-4&search%5Bfilter_enum_generation%5D%5B1%5D=gen-vw-polo-5&search%5Bfilter_float_price%3Afrom%5D=100&search%5Bfilter_float_price%3Ato%5D=20000&search%5Bfilter_float_year%3Ato%5D=2021&search%5Bfilter_float_mileage%3Afrom%5D=1000&search%5Border%5D=filter_float_price%3Aasc&page=2
#ttps://www.autovit.ro/autoturisme/volkswagen/polo?search%5Bfilter_enum_fuel_type%5D=petrol&search%5Bfilter_float_mileage%3Ato%5D=270000&search%5Bfilter_enum_generation%5D%5B0%5D=gen-vw-polo-4&search%5Bfilter_enum_generation%5D%5B1%5D=gen-vw-polo-5&search%5Bfilter_float_price%3Afrom%5D=100&search%5Bfilter_float_price%3Ato%5D=20000&search%5Bfilter_float_year%3Ato%5D=2021&search%5Bfilter_float_mileage%3Afrom%5D=1000&search%5Border%5D=filter_float_price%3Aasc
