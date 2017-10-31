#include "AdapterRepositories.h"
#include "SailRoute.h"
#include "KeyValuePair.h"
#include "FileHandler.h"
#include "CSVInterperter.h"
#include "Product.h"
#include "Cannon.h"


AdapterRepositories::AdapterRepositories()
{
}


AdapterRepositories::~AdapterRepositories()
{
}


Vector<KeyValuePair<Ship, int>> AdapterRepositories::create_ship_shop_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("schepen.csv");

	auto result = CSVInterperter::create_columns(file_handler);

	// Create [Ship, price]
	// This can be encapsulated to a Map<K, V>
	Vector<KeyValuePair<Ship, int>> ship_shop_adapter;
	for (int i = 0; i < result.used(); i++)
	{
		const auto line = result[i];
		const Ship ship{
			line[0].value(),
			String::stoi(line[2].value()),
			String::stoi(line[3].value()),
			String::stoi(line[4].value()),
			line[5].value()
		};

		const KeyValuePair<Ship, int> kv{ ship, String::stoi(line[1].value()) };

		ship_shop_adapter.push_back(kv);
	}

	return ship_shop_adapter;
}

Vector<KeyValuePair<String, Vector<Product>>> AdapterRepositories::create_goods_shop_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("goederen prijzen.csv");

	auto result = CSVInterperter::create_columns(file_handler);

	// Create [City_name, [goods_name, span_amount]]
	Vector<KeyValuePair<String, Vector<Product>>> goods_adapter;
	for (int i = 0; i < result.used(); i++)
	{
		String city;
		Vector<Product> goods;
		const auto line = result[i];
		for (int j = 0; j < line.used(); j++)
		{
			const auto& value = line[j];
			if (value.key() == "")
			{
				city = value.value();
				continue;
			}

			Product p{ value.key(), value.value() };
			goods.push_back(p);
		}

		KeyValuePair<String, Vector<Product>> kv{ city, goods };
		goods_adapter.push_back(kv);
	}

	return goods_adapter;
}

Vector<Cannon> AdapterRepositories::create_cannons_adapter()
{
	Vector<Cannon> result;

	result.push_back(Cannon{ "light", "0-5", 50 });
	result.push_back(Cannon{ "medium", "0-3", 200 });
	result.push_back(Cannon{ "heavy", "0-2", 1000 });

	return result;
}

Vector<KeyValuePair<String, Vector<SailRoute>>> AdapterRepositories::create_routes_adapter()
{
	FileHandler file_handler;
	file_handler.load_file("afstanden tussen steden.csv");

	auto result = CSVInterperter::create_columns(file_handler);
	Vector<KeyValuePair<String, Vector<SailRoute>>> adapter;

	for (int i = 0; i < result.used(); i++)
	{
		String from;
		Vector<SailRoute> routes;
		const auto line = result[i];
		for (int j = 0; j < line.used(); j++)
		{
			const auto& value = line[j];
			if (value.key() == "")
			{
				from = std::move(value.value());
				continue;
			}

			const SailRoute r{ from, value.key(), String::stoi(value.value()) };
			routes.push_back(r);
		}

		const KeyValuePair<String, Vector<SailRoute>> kv{ from, routes };
		adapter.push_back(kv);
	}

	return adapter;
}
