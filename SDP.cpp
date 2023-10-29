#include <iostream>
#include <vector>
#include <memory>

// Observer
class StockMarketObserver {
public:
    virtual void update(double stockData) = 0;
    virtual ~StockMarketObserver(){}
};


// Subject
class StockMarket {
public:
    void registerObserver(StockMarketObserver* observer) {
        observers.push_back(observer);
    }

    void unregisterObserver(StockMarketObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void updateStockData(double stockData) {
        for (StockMarketObserver* observer : observers) 
            observer->update(stockData);
    }

private:
    std::vector<StockMarketObserver*> observers;
};

// Concrete Observer
class StockDisplay : public StockMarketObserver {
public:
    void update(double stockData) override {
        std::cout << "Stock Display: Received update - " << stockData << std::endl;
    }
};

class StockLog : public StockMarketObserver {
public:
    void update(double stockData) override {
        std::cout << "Stock Log: Received update - " << stockData << std::endl;
    }
};

int main() {
    StockMarket stockMarket;

    auto display = std::make_unique<StockDisplay>();
    auto log = std::make_unique<StockLog>();

    stockMarket.registerObserver(display.get());
    stockMarket.registerObserver(log.get());

    stockMarket.updateStockData(150.0);
    stockMarket.updateStockData(155.0);

    stockMarket.unregisterObserver(display.get());
}
