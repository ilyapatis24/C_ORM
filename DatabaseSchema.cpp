#include "DatabaseSchema.h"

namespace DatabaseSchema
{
	void createSchema(Wt::Dbo::Session& session)
	{
		session.createTables();
	}

	void createRandomStocksAndSales(Wt::Dbo::Session& session, std::vector<Wt::Dbo::ptr<Shop>>& shopList, Wt::Dbo::ptr<Book>& bookPtr)
	{
		auto stockCount = rand() % shopList.size();
		for (auto i = 0; i < stockCount; i++)
		{
			auto shopNumber = rand() % shopList.size();
			auto shopPtr = shopList[shopNumber];
			std::unique_ptr<Stock> stock{ new Stock() };
			stock->count = rand() % 100;
			auto stockPtr = session.add(std::move(stock));
			stockPtr.modify()->book = bookPtr;
			stockPtr.modify()->shop = shopPtr;

			auto salesCount = rand() % 5;
			for (auto i = 0; i < salesCount; i++)
			{
				auto price = static_cast<double>(rand() % 2000);
				Wt::WDate date(2022, rand() % 12 + 1, rand() % 30 + 1);
				std::unique_ptr<Sale> sale{ new Sale() };
				sale->count = rand() % 2;
				sale->dateSale = date;
				sale->price = price;
				auto salePtr = session.add(std::move(sale));
				salePtr.modify()->stock = stockPtr;
			}
		}
	}

	void createSampleData(Wt::Dbo::Session& session)
	{

		Wt::Dbo::Transaction transaction{ session };

		// Создаем магазины

		std::vector<Wt::Dbo::ptr<Shop>> shopList;

		Wt::Dbo::ptr<Shop> shopPtr1 = session.add(std::move(std::make_unique<Shop>(Shop{"Буквоед"})));
		shopList.push_back(shopPtr1);
		Wt::Dbo::ptr<Shop> shopPtr2 = session.add(std::move(std::make_unique<Shop>(Shop{"Питер Пэн"})));
		shopList.push_back(shopPtr2);

		{
			auto shopPtr = session.add<Shop>(std::make_unique<Shop>(Shop{"Библиосфера"}));
			shopList.push_back(shopPtr);
		}

		// Создаем издателей, их книги и склады
		{
			std::string name("Вильямс");
			Wt::Dbo::ptr<Publisher> publisherPtr = session.find<Publisher>().where("name = ?").bind(name);
			if (!publisherPtr)
			{
				std::unique_ptr<Publisher> publisher{ new Publisher() };
				publisher->name = name;
				publisherPtr = session.add(std::move(publisher));
			}

			auto bookPtr = session.add<Book>(std::make_unique<Book>(Book{"Программист-прагматик / Дэвид Томас, Эндрю Хант."}));
			bookPtr.modify()->publisher = publisherPtr;
			createRandomStocksAndSales(session, shopList, bookPtr);

		}

		{
			std::string name("Питер");
			Wt::Dbo::ptr<Publisher> publisherPtr = session.find<Publisher>().where("name = ?").bind(name);
			if (!publisherPtr)
			{
				std::unique_ptr<Publisher> publisher{ new Publisher() };
				publisher->name = name;
				publisherPtr = session.add(std::move(publisher));
			}

			auto bookPtr = session.add<Book>(std::make_unique<Book>(Book{"Чистый код / Роберт Мартин."}));
			bookPtr.modify()->publisher = publisherPtr;
			createRandomStocksAndSales(session, shopList, bookPtr);

		}

		{
			std::string name("Питер");
			Wt::Dbo::ptr<Publisher> publisherPtr = session.find<Publisher>().where("name = ?").bind(name);
			if (!publisherPtr)
			{
				std::unique_ptr<Publisher> publisher{ new Publisher() };
				publisher->name = name;
				publisherPtr = session.add(std::move(publisher));
			}

			auto bookPtr = session.add<Book>(std::make_unique<Book>(Book{"Head First. Паттерны проектирования / Эрик Фримен."}));
			bookPtr.modify()->publisher = publisherPtr;
			createRandomStocksAndSales(session, shopList, bookPtr);

		}

		{
			std::string name("Форум");
			Wt::Dbo::ptr<Publisher> publisherPtr = session.find<Publisher>().where("name = ?").bind(name);
			if (!publisherPtr)
			{
				std::unique_ptr<Publisher> publisher{ new Publisher() };
				publisher->name = name;
				publisherPtr = session.add(std::move(publisher));
			}

			auto bookPtr = session.add<Book>(std::make_unique<Book>(Book{"Грокаем алгоритмы / Адитья Бхаргава."}));
			bookPtr.modify()->publisher = publisherPtr;
			createRandomStocksAndSales(session, shopList, bookPtr);

		}

		transaction.commit();
	}

	std::vector<Wt::Dbo::ptr<Publisher>> getPublishers(Wt::Dbo::Session& session)
	{
		Wt::Dbo::Transaction transaction{ session };
		std::vector<Wt::Dbo::ptr<Publisher>> res;
		Wt::Dbo::collection<Wt::Dbo::ptr<Publisher>> publishers = session.find<Publisher>();
		for (const Wt::Dbo::ptr<Publisher>& item : publishers)
		{
			res.push_back(item);
		}

		return res;
	}

	std::vector<Wt::Dbo::ptr<Shop>> getShops(Wt::Dbo::Session& session, Wt::Dbo::dbo_default_traits::IdType publisherId)
	{
		Wt::Dbo::Transaction transaction{ session };
		std::vector<Wt::Dbo::ptr<Shop>> res;
		std::string query = "SELECT DISTINCT s\
			FROM\
			shop s\
			JOIN stock st ON st.shop_id = s.id\
			JOIN book b ON st.book_id = b.id\
			JOIN publisher p ON b.publisher_id = p.id\
			WHERE p.id = ?";

		Wt::Dbo::collection<Wt::Dbo::ptr<Shop>> shops = session.query<Wt::Dbo::ptr<Shop>>(query).bind(publisherId);
		for (const Wt::Dbo::ptr<Shop>& item : shops)
		{
			res.push_back(item);
		}

		return res;
	}
}