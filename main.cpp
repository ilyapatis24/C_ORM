#include "DatabaseScheme.h"
#include <vector>
#include <Windows.h>


void findShop(Wt::Dbo::Session& session, std::string namePublisher);

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");
	try {
		std::string connection =
			"host=localhost "
			"port=5432 "
			"dbname=books "
			"user=postgres "
			"password=postgres";

		std::unique_ptr<Wt::Dbo::backend::Postgres> postgres = std::make_unique<Wt::Dbo::backend::Postgres>(connection);
		Wt::Dbo::Session session;
		session.setConnection(std::move(postgres));
		session.mapClass<Publisher>("publisher");
		session.mapClass<Book>("book");
		session.mapClass<Shop>("shop");
		session.mapClass<Stock>("stock");
		session.mapClass<Sale>("sale");
		try {

			session.createTables();
		}
		catch (const Wt::Dbo::Exception& ex) {
			std::cout << ex.what() << std::endl;
		}

		Wt::Dbo::Transaction tx(session);
		std::unique_ptr<Publisher> Litres{ new Publisher() };
		Litres->name = "Litres";
		Wt::Dbo::ptr<Publisher> Litres_ptr = session.add(std::move(Litres));
		std::unique_ptr<Publisher> Labirint{ new Publisher() };
		Labirint->name = "Labirint";
		Wt::Dbo::ptr<Publisher> Labirint_ptr = session.add(std::move(Labirint));
		std::unique_ptr<Publisher> Eksmo{ new Publisher() };
		Eksmo->name = "Eksmo";
		Wt::Dbo::ptr<Publisher> Eksmo_ptr = session.add(std::move(Eksmo));


		std::unique_ptr <Book> warAndPeace_1{ new Book() };
		warAndPeace_1->title = "War and Peace";
		warAndPeace_1->publisher = Litres_ptr;
		Wt::Dbo::ptr<Book> warAndPeace_1_ptr = session.add(std::move(warAndPeace_1));
		std::unique_ptr <Book> warAndPeace_2{ new Book() };
		warAndPeace_2->title = "War and Peace";
		warAndPeace_2->publisher = Labirint_ptr;
		Wt::Dbo::ptr<Book> warAndPeace_2_ptr = session.add(std::move(warAndPeace_2));
		std::unique_ptr <Book> warAndPeace_3{ new Book() };
		warAndPeace_3->title = "War and Peace";
		warAndPeace_3->publisher = Eksmo_ptr;
		Wt::Dbo::ptr<Book> warAndPeace_3_ptr = session.add(std::move(warAndPeace_3));
		std::unique_ptr <Book> masterAndMargarita_1{ new Book() };
		masterAndMargarita_1->title = "Master and Margarita";
		masterAndMargarita_1->publisher = Litres_ptr;
		Wt::Dbo::ptr<Book> masterAndMargarita_1_ptr = session.add(std::move(masterAndMargarita_1));
		std::unique_ptr <Book> masterAndMargarita_2{ new Book() };
		masterAndMargarita_2->title = "Master and Margarita";
		masterAndMargarita_2->publisher = Eksmo_ptr;
		Wt::Dbo::ptr<Book> masterAndMargarita_2_ptr = session.add(std::move(masterAndMargarita_2));
		std::unique_ptr <Book> mertvieDushi_1{ new Book() };
		mertvieDushi_1->title = "Mertvie dushi";
		mertvieDushi_1->publisher = Litres_ptr;
		Wt::Dbo::ptr<Book> mertvieDushi_1_ptr = session.add(std::move(mertvieDushi_1));
		std::unique_ptr <Book> mertvieDushi_2{ new Book() };
		mertvieDushi_2->title = "Mertvie dushi";
		mertvieDushi_2->publisher = Labirint_ptr;
		Wt::Dbo::ptr<Book> mertvieDushi_2_ptr = session.add(std::move(mertvieDushi_2));


		std::unique_ptr<Shop> chitayGorod{ new Shop() };
		chitayGorod->name = "chitayGorod";
		Wt::Dbo::ptr<Shop> chitayGorod_ptr = session.add(std::move(chitayGorod));
		std::unique_ptr<Shop> domKnigi{ new Shop() };
		domKnigi->name = "domKnigi";
		Wt::Dbo::ptr<Shop> domKnigi_ptr = session.add(std::move(domKnigi));
		std::unique_ptr<Shop> knigi{ new Shop() };
		knigi->name = "knigi";
		Wt::Dbo::ptr<Shop> knigi_ptr = session.add(std::move(knigi));

		std::unique_ptr<Stock> stockMoscow_1{ new Stock() };
		stockMoscow_1->book = warAndPeace_1_ptr;
		stockMoscow_1->shop = chitayGorod_ptr;
		stockMoscow_1->count = 100;
		Wt::Dbo::ptr<Stock> stockMoscow_ptr_1 = session.add(std::move(stockMoscow_1));
		std::unique_ptr<Stock> stockMoscow_2{ new Stock() };
		stockMoscow_2->book = masterAndMargarita_2_ptr;
		stockMoscow_2->shop = chitayGorod_ptr;
		stockMoscow_2->count = 120;
		Wt::Dbo::ptr<Stock> stockMoscow_ptr_2 = session.add(std::move(stockMoscow_2));
		std::unique_ptr<Stock> stockMoscow_3{ new Stock() };
		stockMoscow_3->book = mertvieDushi_1_ptr;
		stockMoscow_3->shop = domKnigi_ptr;
		stockMoscow_3->count = 130;
		Wt::Dbo::ptr<Stock> stockMoscow_ptr_3 = session.add(std::move(stockMoscow_3));
		std::unique_ptr<Stock> stockMoscow_4{ new Stock() };
		stockMoscow_4->book = warAndPeace_3_ptr;
		stockMoscow_4->shop = knigi_ptr;
		stockMoscow_4->count = 100;
		Wt::Dbo::ptr<Stock> stockMoscow_ptr_4 = session.add(std::move(stockMoscow_4));

		std::unique_ptr<Sale> sale_1{ new Sale() };
		sale_1->price = 100;
		sale_1->date_sale = "2023-07-02";
		sale_1->stock = stockMoscow_ptr_1;
		sale_1->count = 10;
		session.add(std::move(sale_1));
		std::unique_ptr<Sale> sale_2{ new Sale() };
		sale_2->price = 90;
		sale_2->date_sale = "2023-07-02";
		sale_2->stock = stockMoscow_ptr_2;
		sale_2->count = 20;
		session.add(std::move(sale_2));
		std::unique_ptr<Sale> sale_3{ new Sale() };
		sale_3->price = 110;
		sale_3->date_sale = "2023-07-02";
		sale_3->stock = stockMoscow_ptr_3;
		sale_3->count = 30;
		session.add(std::move(sale_3));
		std::unique_ptr<Sale> sale_4{ new Sale() };
		sale_4->price = 115;
		sale_4->date_sale = "2023-07-02";
		sale_4->stock = stockMoscow_ptr_4;
		sale_4->count = 60;
		session.add(std::move(sale_4));
		std::string namePublisher;
		std::cout << "Input name of publisher: ";
		std::cin >> namePublisher;
		findShop(session, namePublisher);
		tx.commit();

	}
	catch (Wt::Dbo::Exception& e) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}

void findShop(Wt::Dbo::Session& session, std::string namePublisher) {
	Wt::Dbo::ptr<Publisher> findPublisher = session.find<Publisher>().where("name = ?").bind(namePublisher);
	Wt::Dbo::collection<Wt::Dbo::ptr<Book>> books = session.find<Book>().where("publisher_id = ?").bind(findPublisher);
	std::vector<Wt::Dbo::collection<Wt::Dbo::ptr<Stock>>> stocks;
	for (const auto& id : books) {
		stocks.push_back(session.find<Stock>().where("book_id = ?").bind(id.id()));
	}
	std::vector<Wt::Dbo::collection<Wt::Dbo::ptr<Shop>>> shops;
	for (const auto& col : stocks) {
		for (const auto& id : col) {
			shops.push_back(session.find<Shop>().where("id = ?").bind(id->shop));
		}
	}
	std::cout << "Shops with books of " << namePublisher << ": \n";
	std::set<std::string> names;
	for (const auto& col : shops) {
		for (const auto& id : col) {
			names.insert(id->name);
		}
	}
	for (const auto& name : names) {
		std::cout << name << std::endl;
	}
}