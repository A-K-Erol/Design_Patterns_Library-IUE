import java.util.HashMap;
import java.util.ArrayList;
import java.util.List;

/*
Classes:
1. Stock (Subject): Knows its managers and implements Attach, Detach, and Notify accordingly. Managers
are shared by all stocks.
    a. IBM : Concrete Stock that lets client set price for testing purposes.

2. Mediator: Contains a hashmap of observer/subject pairs that can be modified by observer via subject.
    a. UpManager : Notifies observer if notify() is called and price increased
    b. DownManager : Notifies observer if notify() is called and price decreased

3. Observer (Abstract Observer): interface for updating observer.
    a. Investor (Concrete Observer): Maintains a reference to a ConcreteSubject object.
Stores state that should stay consistent with the subject's. Implements the Observer
updating interface to keep its state consistent with the subject's.

 */

//'Subject' ==> Stock
abstract class Stock {
    public Stock(String symbol, double price) {
        _symbol = symbol;
        _price = price;
        _last_price = price;
    }
    //Register the Observers
    public void Attach (Investor investor, char mode) {
        if (mode == 'U' || mode == 'u'){
            managers.get(0).attach(investor, this);
        }
        else if (mode == 'D' || mode == 'd') {
            managers.get(1).attach(investor, this);
        }
        else {System.out.println("Invalid Mode: 'U' or 'D' only.");}
    }
    //Unregister (a) from all managers or (b) from a specific mode. Overloaded function.
    public void Detach(Investor investor){
        for (Mediator manager : managers){
            manager.detach(investor);
        }
    }
    public void Detach (Investor investor, char mode){
        if (mode == 'U' || mode == 'u'){
            managers.get(0).detach(investor);
        }
        else if (mode == 'D' || mode == 'd') {
            managers.get(1).detach(investor);
        }
    }

    //Notify the Observers.
    public void Notify() {
        // set argument to something that helps
        // tell the Observers what happened
        for (Mediator manager : managers) {
            manager.Notify(this);
        }
    }
    public String getSymbol() {return _symbol;}
    void setSymbol(String value) {_symbol = value;}
    public double	getPrice() {return _price;}
    public double   getLastPrice() {return _last_price;}
    abstract public void setPrice(double value);
    protected String _symbol;          // Internal Subject state
    protected double _price;			// Internal Subject state
    protected double _last_price;        // Internal Subject state
    protected static ArrayList<Mediator> managers =
            new ArrayList<>(List.of(new UpManager(), new DownManager()));
    // all stocks share the same two managers
}
//'ConcreteSubject' ==> IBM
class IBM extends Stock {
    // Constructor
    public IBM(String symbol, double price) {
        super(symbol, price);
    }
    public void setPrice(double value) {
        // Whenever a change happens to _price, notify
        // observers.
        _last_price = _price;
        _price = value;
        Notify();
    }
}

// The Mediator
class Mediator {
    public Mediator(){
        investorStockPairs = new HashMap<>();
    }
    public void attach(Investor investor, Stock stock){
        investorStockPairs.put(investor, stock);
    }
    public void detach(Investor investor){
        investorStockPairs.remove(investor);
    }
    public void Notify(Stock stock){
        for (Investor i : investorStockPairs.keySet()){
            i.Update(investorStockPairs.get(i));
        }
    }
    protected HashMap<Investor, Stock> investorStockPairs;
}

class UpManager extends Mediator{
    public void Notify(Stock stock){
        for (Investor i : investorStockPairs.keySet()){
            if (investorStockPairs.get(i) == stock) {
                if (stock._price > stock._last_price){
                    i.Update(stock);
                }
            }
        }
    }
}

class DownManager extends Mediator{
    public void Notify(Stock stock){
        for (Investor i : investorStockPairs.keySet()){
            if (investorStockPairs.get(i) == stock) {
                if (stock._price < stock._last_price){
                    i.Update(stock);
                }
            }
        }
    }
}

//'Observer'  ==> Abstract Observer.
interface Observer {
    void Update(Stock stock);
}

//'ConcreteObserver' ==> Investor
class Investor implements Observer {
    private Stock _stock;
    private final String _investor_name;
    private double _stock_price;	// Internal Observer state
    // Constructor
    public Investor(String name) {
        _investor_name = name;
    }
    public void Update(Stock stock) {
        _stock = stock; 				 // Reference to Subject
        _stock_price = stock.getPrice();
        // Internal Observer state
        String _stock_name = stock.getSymbol();
        System.out.println("Notified " + _investor_name + " of " + _stock_name +
                "'s " + "change to " + _stock_price);
    }
    public Stock getStock() { return _stock; }
    public void setStock(Stock value) { _stock = value; }
    public String getName() { return _investor_name; }
}

public class StockMediator {
    public static void main(String[] args) {
        // Create investors
        Investor s = new Investor("Ahmet");
        Investor b = new Investor("Berna");

        // Create IBM stock and attach investors
        IBM ibm = new IBM("IBM", 120.00);
        s.setStock(ibm);
        b.setStock(ibm);
        ibm.Attach(s, 'U');
        ibm.Attach(b, 'D');

        // Change price, which notifies investors
        ibm.setPrice(120.10);
        ibm.setPrice(121.00);
        ibm.setPrice(120.50);
        ibm.setPrice(120.75);

        System.out.println("\nMoving Berna from Down to Up Notification list");
        ibm.Detach(b, 'D');
        ibm.Attach(b, 'U');

        ibm.setPrice(120.10);
        ibm.setPrice(121.00);
        ibm.setPrice(120.50);
        ibm.setPrice(120.75);

        System.out.println("\nRemoving Ahmet from all notification lists");
        ibm.Detach(s);

        ibm.setPrice(120.10);
        ibm.setPrice(121.00);
        ibm.setPrice(120.50);
        ibm.setPrice(120.75);
    }
}