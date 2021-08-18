# -*- coding: utf-8 -*-
from odoo import fields, models


class Customer(models.Model):
    _name = 'supermarket.customer'
    _description = 'Customer'

    name = fields.Char('Name',required= True)
    email = fields.Char('Email')
    city = fields.Char('City')
    street = fields.Char('Street')
    IsPremiumCustomer=fields.Boolean('Premium Customer')
    
class ProductCatagory(models.Model);
    _name='supermarket.ProductCatagory'
    _description='ProductCatagory'

    name = fields.Char('Name',required=True)

class Product(models.Model)
    _name='supermarket.Product'
    _description='supermarket.Product'
    name = fields.Char('Name',required=True)
    ProductCatagory= fields.ProductCatagory()#i did not saw how to make a nested module in the documentation or videos and use many2one 
    unitPrice= fields.float('Price',required=True)

class Cart(models.Model)
    _name='supermarket.Cart'
    _description='supermarket.Cart'    

    Customer=fields.One2one.Customer('Customer',required=True) #useone2one realtion
    DataOfCreation=fields.Date('Date Of Creation')
    TotalAmount=fields.float(compute= '_compute_totalAmount')
    deserveDiscount=fields.Boolean(relatied='Customer.IsPremiumCustomer',store=True)
    @api.depends('Quantity','unitPrice')
    def _compute_totalAmount(self)
        for record in self
            record.TotalAmount = record.TotalAmount+ (record.Quantity*record)

        if deserveDiscount==True
            record.TotalAmount=record.TotalAmount*0.9

#Not sure how to get paramaters to function,I made a related field if the customer is premim user then i will give him 10% discount 



class CartItem(models.Model)
    _name='supermarket.CartItem'
    _description='supermarket.CartItem'

     Product= fields.Product('Product')
     Quantity=fields.Integer('Quantity')
     Cart=fields.Many2One('Cart')


"""
I think there is a way to improve the funcionality, due the time limit and the

I thougth about learning more about the nested modules instead inheritence.
And i think CartItem Should be a field in Cart with One2Many Relation.
Didn't saw a way to create relation with types in the documentation such as one2one with customer,how do they know the type?

In case of Premium Customer, there are no ways to know how the customer is a a premium customer.
I am going to assert if the customer is premium with boolean option.If he is i give 10% discount
with realation fields
"""





  