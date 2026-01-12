package models.products;

import database.EmbeddedDatabaseService;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Merchandise extends Product {
    private int stock;
    public Merchandise(String name, double price, int stock) {
        super(name, price);
        this.stock = stock;
    }
    public Merchandise(String id, String name, double price, int stock) {
        super(id, name, price);
        this.stock = stock;
    }

    public int getStock(){
        return this.stock;
    }

    public void setStock(int stock){
        this.stock = stock;
    }

    @Override
    public String toString() {
        return super.toString() + "\n\t This merchandise has a stock of " + this.stock;
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into merchandise(id, name, price, discount, stock) values(?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.name);
        statement.setString(3, Double.toString(this.price));
        statement.setString(4, Double.toString(this.getDiscount()));
        statement.setString(5, Integer.toString(this.stock));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update merchandise set name=?, price=?, discount=?, stock=? where id=?");

        statement.setString(5, this.getId());
        statement.setString(1, this.name);
        statement.setString(2, Double.toString(this.price));
        statement.setString(3, Double.toString(this.getDiscount()));
        statement.setString(4, Integer.toString(this.stock));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from merchandise where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
