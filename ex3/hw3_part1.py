



#gets a text file path, reads it and returns a dictionary holding the inventory data    
def readFile(file_name):
    #creating an empty dictionary to hold the products and their info
    inventory = {}
    #open the given file to read from it
    f = open(file_name,'r')
    #reading line by line
    for line in f:
        #splitting the command into the first two words and the rest of the line.
        input = line.split(" ",2)
        #assembling back the command(['add','product'] => 'add product')
        command = input.pop(0) + ' ' + input.pop(0)
        #Add product command
        if command == 'add product':
            #splits the arugemnt into list of the product name, it's price and amount.
            args = input.pop().split(' ')
            name = args[0] #first arg is name
            price = float(args[1]) #second arg is price
            amount = float(args[2]) # third arg is amount
            #checking if the price and amount are valid and if the product does not exist already
            if(price >= 0 and amount >= 0 and not(name in inventory)): 
                #adds the product into the dictionary with the correspoinding values.
                inventory[name] = {'price' : price, 'amount' : amount, 'profit' : 0 }
        #Change amount command
        elif command == 'change amount':
            args = input.pop().split(' ')#splits the arugemnt into list of the product name, and it's new amount.
            name = args[0] #first arg is name
            newAmount = float(args[1]) #second arg is the new amount
            if name in inventory: #only change the amount if the product actually exists already
                inventory[name]['amount'] += newAmount
        #Ship order command
        elif command == 'ship order':
            order = input.pop().split(' -- ') #splits the arugemnt into a list, each element is a product and it's amount
            for entry in order: #iterating over all the products in the order
                name = entry.split(', ')[0] # extracting the name from the string
                amount = float(entry.split(', ')[1]) # extracting the amount from the string
                #Skip the product if it does not exist or amount is less than 1
                if(name in inventory and inventory[name]['amount'] > 0): 
                    if(inventory[name]['amount'] >= amount): #check if the amount in the inventory is enough to ship
                        inventory[name]['amount'] -= amount #deducts the amount from the inventory
                        inventory[name]['profit'] += amount*inventory[name]['price'] #records the profit that we gained
                    
    return inventory #returns the finished data.


#gets a text file path and returns a tuple containing the most profitable product
def find_best_selling_product(file_name):
    inventory = readFile(file_name) #reads the file
    bestSeller = {'name' : '', 'profit' : 0} #temp variable to hold the best seller so far.
    for key,value in inventory.items(): #iterating over all the products in the inventory
        #change the best seller if the profit is greater, or the profit is the same but the product name is lexicographicly lower
        if(value['profit'] > bestSeller['profit'] or ((value['profit'] == bestSeller['profit']) and (bestSeller['name'] > key))):
            bestSeller['name'] = key
            bestSeller['profit'] = value['profit']
    #returns the best seller in a tuple format.
    return (bestSeller['name'], bestSeller['profit'])


#gets a text file path and returns the K most expensice products in the inventory
def find_k_most_expensive_products(file_name, k):
    if k <= 0: #returns an empty dict if k is less than 1
        return []
    inventory = readFile(file_name) #reads the file
    
    priceDict = {} #price dict will hold all of the products with the prices as a keys and product name lists as values.
    #building priceDict
    for key,product in inventory.items(): # iterating over all products in the inventory
        #if product's price is not a key in the dict, create it and make an empty list for names.
        if(not(product['price'] in priceDict)):
            priceDict[product['price']] = []
        priceDict[product['price']].append(key) #insert the current product into the list under his price.
    #iterating over all prices in priceDict to sort the name lists by lexicographic order.
    for entry in priceDict.values():
        entry.sort()#sorting each list in the price dict.
    items = priceDict.items()#creating a list with all dictionary keys with values so we can sort the name lists by prices.
    sorted_items=sorted(items,reverse=True)#sorts the lists by price
    resultList = []# creating a list that will hold the K most expensive products
    for entry in sorted_items:
        #each entry is a 2 item list, [price,[productName1, productName2, ... ]]
        products = entry[1]#products is a list that holds all the products with the same price 
        for product in products:
            resultList.append(product) #inserts the product names into the result list by lexicographic order.
            if(len(resultList) == k):
                return resultList #if we have k elements in resultList, return it.
    #if we got here,  there's less than K products in the inventory therefore returns all of them 
    return resultList



