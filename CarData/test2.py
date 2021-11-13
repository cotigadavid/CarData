import urllib
from urllib.request import urlopen as uReq
from bs4 import BeautifulSoup as soup

fout = open("output.txt", "w")
fin = open("D:/CarData/CarData/linkFile.txt", "r")

ConversionRate = 0.20207

def strip(string):
	rez = ""
	for i in range(0, len(string)):
		if (string[i] != ' ' and string[i] != '\n'):
			rez += string[i]
	return rez

def toInt(string):
	rez = ""
	for i in range(0, len(string)):
		if (ord(string[i]) >= 48 and ord(string[i]) <= 57) or string[i] == ".":
			rez += string[i]
	return rez

def GetConversionRate():
	WiseUrl = "https://www.exchange-rates.org/Rate/RON/EUR"

	uClient = uReq(WiseUrl)
	page_html = uClient.read()
	uClient.close()
	page_soup = soup(page_html, "html.parser")

	ConversionRate = float(toInt(page_soup.find(["td"], class_="text-nowrap text-narrow-screen-wrap result").string))
	return ConversionRate

def ProcessLink(link):
	F_my_url = link;
	try:
		F_uClient = uReq(F_my_url)
	except urllib.error.HTTPError:
		return
	F_page_html = F_uClient.read()
	F_uClient.close()

	F_page_soup = soup(F_page_html, "html.parser")

	runOut = F_page_soup.findAll(["h6"], class_="css-1tcorc4-Text eu5v0x0");

	if len(runOut):
		return

	#if len(F_page_soup.findAll(["body"], class_="autovitro  detailpage desktop")):
	#	print("NICE")

	please = F_page_soup.findAll(["body"], class_="autovitro")

	if len(please) == 0:
		proprietati = F_page_soup.findAll(["li"], class_="css-ox1ptj")

		pret = F_page_soup.find(["h3"], class_="css-okktvh-Text eu5v0x0")

		if pret.contents[0] == "Schimb":
			return

		ok = 0
		for prop in proprietati:
			if "An de fabricatie" in prop.p.string:
				ok = ok + 1
			if "Rulaj" in prop.p.string:
				ok = ok + 1

		if (ok != 2):
			return

		fout.write("olx ")
		for prop in proprietati:
			if "An de fabricatie" in prop.p.string:
				fout.write(prop.p.string)
			#if "Capacitate motor" in prop.p.string:
				#print(prop.p.string)
			if "Rulaj" in prop.p.string:
				fout.write(prop.p.string + " ")
		if (pret.contents[4] == "lei"):
			fout.write(str(int(int(strip(pret.contents[0])) * ConversionRate)))
		else:
			fout.write(pret.contents[0])
		print(pret.contents[0])

	else:
		fout.write("aut ")
		
		pret = F_page_soup.findAll(["div"], class_="offer-price")[1]
		proprietati = F_page_soup.findAll(["span"], class_="offer-main-params__item")

		fout.write("An de fabricatie: " + str(int(proprietati[0].contents[0])) + " ")
		fout.write("Rulaj: " + strip(proprietati[1].contents[0]) + " ")

		currency = pret.span.contents[1].string;
		if currency == "RON":
			fout.write(str(int(int(strip(pret.get("data-price"))) * ConversionRate)))			
		else:
			fout.write(pret.get("data-price"))
		print(pret.get("data-price"))

	fout.write('\n')

def main():

	ConversionRate = GetConversionRate()

	print(ConversionRate)

	my_urlBase = fin.read()

	try:
		uClient = uReq(my_urlBase)
	except urllib.error.URLError:
		return
	except urllib.error.HTTPError:
		return


	fout.write(str(1 / ConversionRate) + "\n")

	page_html = uClient.read()
	uClient.close()
	page_soup = soup(page_html, "html.parser")

	X = page_soup.findAll(["span"], class_="item fleft");

	nrOfPages = 2
	if len(X):
		nrOfPages = int(X[len(X) - 1].a.span.string);

	pageAddSyntax = "&page="

	for i in range(1, nrOfPages):
		if i != 1:
			my_url = my_urlBase + pageAddSyntax + str(i);

			uClient = uReq(my_url)
			page_html = uClient.read()
			uClient.close()
			page_soup = soup(page_html, "html.parser")

		links = page_soup.findAll(["h3"], class_="lheight22 margintop5")

		for link in links:
			ProcessLink(link.a.get("href"))


main()
fin.close()
fout.close()