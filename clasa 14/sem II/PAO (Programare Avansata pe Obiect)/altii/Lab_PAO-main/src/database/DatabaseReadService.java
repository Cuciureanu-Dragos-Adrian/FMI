package database;

import models.employees.*;
import models.clients.*;
import models.products.*;

import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class DatabaseReadService {

    public static List<Client> readPFs() throws Exception{
        List<Client> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("pf");

        while(query.next())
            result.add(new PF(query.getString("id"), query.getString("firstName"), query.getString("lastName"), query.getString("pnc"), query.getDouble("funds")));

        return result;
    }

    public static List<Client> readPJs() throws Exception{
        List<Client> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("pj");

        while(query.next())
            result.add(new PJ(query.getString("id"), query.getString("name"), query.getString("fic"), query.getDouble("funds")));

        return result;
    }

    public static List<Employee> readManagers() throws Exception {
        List<Employee> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("manager");

        while(query.next())
            result.add(new Manager(query.getString("id"), query.getDouble("salary"), query.getString("firstName"), query.getString("lastName"), query.getString("managerId")));

        return result;
    }

    public static List<Employee> readMechanics() throws Exception {
        List<Employee> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("mechanic");

        while(query.next())
            result.add(new Mechanic(query.getString("id"), query.getDouble("salary"), query.getString("firstName"), query.getString("lastName"), query.getString("managerId")));

        return result;
    }

    public static List<Employee> readSalesmen() throws Exception {
        List<Employee> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("salesman");

        while(query.next())
            result.add(new Salesman(query.getString("id"), query.getDouble("salary"), query.getString("firstName"), query.getString("lastName"), query.getString("managerId"), query.getInt("saleNr")));

        return result;
    }

    public static List<Product> readMerchandise() throws Exception {
        List<Product> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("merchandise");

        while(query.next())
            result.add(new Merchandise(query.getString("id"), query.getString("name"), query.getDouble("price"), query.getInt("stock")));

        return result;
    }

    public static List<Product> readCars() throws Exception {
        List<Product> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("car");

        while(query.next())
            result.add(new Car(query.getString("id"), query.getString("name"), query.getDouble("price"), query.getInt("wheelNumber"), query.getInt("doorNumber"), query.getInt("seatNumber"), query.getString("carType")));

        return result;
    }

    public static List<Product> readUtilityVehicles() throws Exception {
        List<Product> result = new ArrayList<>();

        ResultSet query = EmbeddedDatabaseService.readAllFromTable("utilityVehicle");

        while(query.next())
            result.add(new UtilityVehicle(query.getString("id"), query.getString("name"), query.getDouble("price"), query.getInt("wheelNumber"), query.getInt("doorNumber"), query.getInt("seatNumber"), query.getDouble("maxLoad"), query.getString("utilityType")));

        return result;
    }
}
