#!/usr/bin/python3

from lxml import html
import requests

address = "https://hobbyking.com/en_us/kiss-esc-2-5s-24a-race-edition-32bit-brushless-motor-ctrl.html"
page = requests.get(address)
tree = html.fromstring(page.content)
in_stock = tree.xpath('//*[@id="product_addtocart_form"]/div[5]/div[1]/div[5]/div[2]/div[2]/label[2]/text()')

print (in_stock)
