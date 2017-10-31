#pragma once
#include "KeyValuePair.h"
#include "SailRoute.h"
#include "Cannon.h"
#include "AdapterRepositories.h"
#include "Product.h"

class AdapterRepositories
{
public:
	AdapterRepositories();
	~AdapterRepositories();
	static Vector<KeyValuePair<Ship, int>> create_ship_shop_adapter();
	static Vector<KeyValuePair<String, Vector<Product>>> create_goods_shop_adapter();
	static Vector<Cannon> create_cannons_adapter();
	static Vector<KeyValuePair<String, Vector<SailRoute>>> create_routes_adapter();
};

