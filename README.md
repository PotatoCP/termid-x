# Termid-x

Termid-x ("Terminal IDX") is a small C++ project that implements a simple order/market engine. Unlike most order book projects, we keep track of order books of many entities. We also keep store the user account that buy or sells each entity.

## Market Engine
This is the core of our project. It stores the open orders, all entities, and all accounts. We also keep track of trade histories here.

The market engine is also the logic handler when we place bid or ask (see `MarketEngine::place_bid` and `MarketEngine::place_ask`). Specifically, it accesses the entity order book and matches the order before inserting the order into `open_orders` hashmap.

## Entity
Each entity will hold its own order book. Instead of using `std::map`, we use reversed `std::vector` to store the (bid and ask) order book. The idea is that `std::vector` has greater locality which makes them efficient. We also reversed the vector to ensure the best (bid and ask) price is at the end of the vector, since the trading activities should be mostly around the best price. This is greatly inspired by http://youtube.com/watch?v=sX2nF1fW7kI.

## Account
Stores the account's information, such as cash balance and owned entities. It also stores the order id that was openned by the account to make it easier to get the order by each account. It also makes it easier to modify the order based on the account (for example deleting all order by a specific account).

## Prerequisites

- A C++ compiler with C++17 support (GCC, Clang, MSVC)
- CMake >= 3.10
- make or ninja to run the build (CMake generator)

On Debian/Ubuntu you can install the essentials with:

```bash
sudo apt update
sudo apt install build-essential cmake
```

## Build & Run

The project uses a conventional out-of-source CMake build. From the repository root (`termid-x`) run:

```bash
cmake ./
cmake --build ./
```

Then run the binary:
```bash
./termid-x
```

## Project layout

- `include/` - public headers for Account, Engine, Entity, Order, Stock, Trade and utilities
- `src/` - implementation files (CPP)
- `CMakeLists.txt` - top-level CMake project file
- `README.md` - this file
