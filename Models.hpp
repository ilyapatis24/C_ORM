#pragma once
#include <iostream>
#include <string>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Windows.h>

#pragma execution_character_set("utf-8")

class Publisher;
class Stock;
class Shop;
class Sale;

class Book
{
public:
	std::string title = "";
	Wt::Dbo::ptr<Publisher> publisher;
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, title, "title");
		Wt::Dbo::belongsTo(a, publisher, "publisher");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "book");
	}
};

class Publisher
{
public:
	std::string name = "";
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books;
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, books, Wt::Dbo::ManyToOne, "publisher");
	}
};


class Stock
{
public:
	int count = 0;
	Wt::Dbo::ptr<Book> book;
	Wt::Dbo::ptr<Shop> shop;
	Wt::Dbo::collection<Wt::Dbo::ptr<Sale>> sales;
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::belongsTo(a, book, "book");
		Wt::Dbo::belongsTo(a, shop, "shop");
		Wt::Dbo::hasMany(a, sales, Wt::Dbo::ManyToOne, "stock");
	}
};

class Shop
{
public:
	std::string name = "";
	Wt::Dbo::collection<Wt::Dbo::ptr<Stock>> stocks;
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, name, "name");
		Wt::Dbo::hasMany(a, stocks, Wt::Dbo::ManyToOne, "shop");
	}
};

class Sale
{
public:
	double price = 0;
	int count = 0;
	Wt::WDate dateSale;
	Wt::Dbo::ptr<Stock> stock;
	template<class Action>
	void persist(Action& a)
	{
		Wt::Dbo::field(a, price, "price");
		Wt::Dbo::field(a, count, "count");
		Wt::Dbo::field(a, dateSale, "date_sale");
		Wt::Dbo::belongsTo(a, stock, "stock");
	}
};
