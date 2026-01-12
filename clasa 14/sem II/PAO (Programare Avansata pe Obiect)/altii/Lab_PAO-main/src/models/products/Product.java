package models.products;

import interfaces.hasId;
import interfaces.persistentWithDb;

public abstract class Product implements hasId, persistentWithDb {

    protected final String id;
    protected final String name;
    protected double price;
    private double discount = 0;
    protected Product(String id, String name, double price){
        this.name = name;
        this.price = price;
        this.id = id;
    }
    protected Product(String name, double price){
        this(java.util.UUID.randomUUID().toString(), name, price);
    }

    /** Returns an item's price.
     *
     * @warning - the discount is also included
     * @return - price - price * discount%
     */

    public String getName(){
        return this.name;
    }
    public double getPrice(){
        return this.price * (100 - discount) / 100;
    }
    public String getId(){
        return this.id;
    }

    public double getDiscount(){
        return this.discount;
    }
    public void setDiscount(double discount) {
        this.discount = discount;
    }

    @Override
    public String toString() {
        return this.name + " with price " + this.price + ", discount " + this.discount + "% and id - " + this.id;
    }
}
