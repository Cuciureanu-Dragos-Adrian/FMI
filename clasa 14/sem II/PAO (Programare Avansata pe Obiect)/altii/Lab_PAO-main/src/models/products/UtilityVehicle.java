package models.products;

import database.EmbeddedDatabaseService;
import models.products.enums.UtilityType;

import java.sql.PreparedStatement;
import java.sql.SQLException;

public class UtilityVehicle extends Vehicle{

    private final double maxLoad;
    private final UtilityType type;

    public UtilityVehicle(String name, double price, int wheelNumber, int doorNumber, int seatNumber, double maxLoad, UtilityType type) {
        super(name, price, wheelNumber, doorNumber, seatNumber);
        this.maxLoad = maxLoad;
        this.type = type;
    }

    public UtilityVehicle(String id, String name, double price, int wheelNumber, int doorNumber, int seatNumber, double maxLoad,  String type) {
        super(id, name, price, wheelNumber, doorNumber, seatNumber);
        this.maxLoad = maxLoad;
        this.type = UtilityType.valueOf(type);
    }

    @Override
    public String toString() {
        return super.toString() + " This utility vehicle has a max load of " + this.maxLoad + " and a type of " + this.type + ".";
    }

    @Override
    public void saveToDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("insert into utilityVehicle(id, name, price, discount, wheelNumber, doorNumber, seatNumber, utilityType, maxLoad) values(?,?,?,?,?,?,?,?,?)");
        statement.setString(1, this.getId());
        statement.setString(2, this.name);
        statement.setString(3, Double.toString(this.price));
        statement.setString(4, Double.toString(this.getDiscount()));
        statement.setString(5, Integer.toString(this.wheelNumber));
        statement.setString(6, Integer.toString(this.doorNumber));
        statement.setString(7, Integer.toString(this.seatNumber));
        statement.setString(8, this.type.toString());
        statement.setString(9, Double.toString(this.maxLoad));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void updateInDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("update utilityVehicle set name=?, price=?, discount=?, wheelNumber=?, doorNumber=?, seatNumber=?, utilityType=?, maxLoad=? where id=?");

        statement.setString(9, this.getId());
        statement.setString(1, this.name);
        statement.setString(2, Double.toString(this.price));
        statement.setString(3, Double.toString(this.getDiscount()));
        statement.setString(4, Integer.toString(this.wheelNumber));
        statement.setString(5, Integer.toString(this.doorNumber));
        statement.setString(6, Integer.toString(this.seatNumber));
        statement.setString(7, this.type.toString());
        statement.setString(8, Double.toString(this.maxLoad));

        EmbeddedDatabaseService.runUpdate(statement);
    }

    @Override
    public void deleteFromDb() throws SQLException {

        PreparedStatement statement = EmbeddedDatabaseService.conn.prepareStatement("delete from utilityVehicle where id=?");

        statement.setString(1, this.getId());

        EmbeddedDatabaseService.runUpdate(statement);
    }
}
