#pragma once
#include "Models.hpp"

namespace DatabaseSchema
{
	void createSchema(Wt::Dbo::Session& session);

	void createRandomStocksAndSales(Wt::Dbo::Session& session, std::vector<Wt::Dbo::ptr<Shop>>& shopList, Wt::Dbo::ptr<Book>& bookPtr);

	void createSampleData(Wt::Dbo::Session& session);

	std::vector<Wt::Dbo::ptr<Publisher>> getPublishers(Wt::Dbo::Session& session);

	std::vector<Wt::Dbo::ptr<Shop>> getShops(Wt::Dbo::Session& session, Wt::Dbo::dbo_default_traits::IdType publisherId);
}
