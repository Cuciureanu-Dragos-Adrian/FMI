package models.products;

import database.EmbeddedDatabaseService;
import models.products.enums.CarType;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class Car extends Vehicle{
    private final CarType type;
    public Car(String name, double price, int wheelNumber, int doorNumber, int seatNumber, CarType type) {
        super(name, price, wheelNumber, doorNumber, seatNumber);
        this.type = type;
    }
    public Car(String id, String name, double price, int wheelNumber, int doorNumber, int seatNumber,  String type) {
        super(id, name, price, wheelNumber, doorNumber, seatNumber);
        this.type = CarType.valueOf(type);
    }
    @Override
    public String toString() {
        return super.toString() + " This car is a " + this.type + ".";
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into car(id, name, price, discount, wheelNumber, doorNumber, seatNumber, carType) values(?,?,?,?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.name);
        statement.setString(3, Double.toString(this.price));
        statement.setString(4, Double.toString(this.getDiscount()));
        statement.setString(5, Integer.toString(this.wheelNumber));
        statement.setString(6, Integer.toString(this.doorNumber));
        statement.setString(7, Integer.toString(this.seatNumber));
        statement.setString(8, this.type.toString());

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update car set name=?, price=?, discount=?, wheelNumber=?, doorNumber=?, seatNumber=?, carType=? where id=?");

        statement.setString(8, this.getId());
        statement.setString(1, this.name);
        statement.setString(2, Double.toString(this.price));
        statement.setString(3, Double.toString(this.getDiscount()));
        statement.setString(4, Integer.toString(this.wheelNumber));
        statement.setString(5, Integer.toString(this.doorNumber));
        statement.setString(6, Integer.toString(this.seatNumber));
        statement.setString(7, this.type.toString());

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from car where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
