package models.clients;

import interfaces.hasId;
import interfaces.persistentWithDb;
import models.products.Merchandise;
import models.products.Product;

import java.util.ArrayList;
import java.util.List;

public abstract class Client implements hasId, Comparable<Client>, persistentWithDb {
    private final String id;
    private double funds;
    private List<String> ownedProducts; // holds the name and quantity of any purchased products
    protected Client(String id, double funds){
        this.id = id;
        this.funds = funds;
        this.ownedProducts = new ArrayList<>();
    }

    //Client without identification
    protected Client(double funds){
        this(java.util.UUID.randomUUID().toString(), funds);
    }

    public String getId(){
        return this.id;
    }

    //sort clients by funds

    public int compareTo(Client o){
        return Double.compare(this.funds, o.funds);
    }

    public double getFunds(){
        return funds;
    }

    public void setFunds(double funds){
        this.funds = funds;
    }

    /** Returns the VAT - Value added tax - for a client
     *
     */
    public abstract int getVAT();

    public void addProduct(Product product, int quantity){
        if (Merchandise.class.isAssignableFrom(product.getClass())) //if merchandise
            this.ownedProducts.add("Merch: " + product.getName() + ", pcs:" + quantity);
        else{ //vehicle
            this.ownedProducts.add("Vehicle: " + product.getName());
        }
    }

    @Override
    public String toString() {
        return "\tId - " + this.id + " with " + this.funds + " available funds. Owns: " + this.ownedProducts;
    }

    public abstract String getFullName();
}
