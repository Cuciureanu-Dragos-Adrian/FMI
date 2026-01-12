package database;

import collections.ClientsCollection;
import collections.EmployeesCollection;
import collections.ProductsCollection;
import org.apache.derby.jdbc.EmbeddedDriver;

import java.sql.*;
public class EmbeddedDatabaseService {
    public static Connection conn;

    public static void initDb(){

        try{
            Driver derbyEmbeddedDriver = new EmbeddedDriver();
            DriverManager.registerDriver(derbyEmbeddedDriver);
            conn = DriverManager.getConnection(EmbeddedDatabaseConstants.ConnString);
            EmployeesCollection.getCollection().readFromDb();
            ProductsCollection.getCollection().readFromDb();
            ClientsCollection.getCollection().readFromDb();
        }
        catch(Exception ex){
            createDb();
            System.out.println("Database paoDb created!");
            initDb();
        }

    }

    public static void runUpdate(PreparedStatement statement) throws SQLException {
        statement.executeUpdate(); //executeUpdate runs insert or update
        conn.commit();
    }

    public static ResultSet readAllFromTable(String tableName) throws Exception {
        Statement statement = conn.createStatement();
        return statement.executeQuery("select * from " + tableName);
    }

    private static void createDb(){

        try {
            Driver derbyEmbeddedDriver = new EmbeddedDriver();
            DriverManager.registerDriver(derbyEmbeddedDriver);
            conn = DriverManager.getConnection(EmbeddedDatabaseConstants.CreateString);
            conn.setAutoCommit(false);

            Statement createPfTable = conn.createStatement();
            createPfTable.execute(EmbeddedDatabaseConstants.CreatePfTable);

            Statement createPjTable = conn.createStatement();
            createPjTable.execute(EmbeddedDatabaseConstants.CreatePjTable);

            Statement createManagerTable = conn.createStatement();
            createManagerTable.execute(EmbeddedDatabaseConstants.CreateManagerTable);

            Statement createMechanicTable = conn.createStatement();
            createMechanicTable.execute(EmbeddedDatabaseConstants.CreateMechanicTable);

            Statement createSalesmanTable = conn.createStatement();
            createSalesmanTable.execute(EmbeddedDatabaseConstants.CreateSalesmanTable);

            Statement createMerchandiseTable = conn.createStatement();
            createMerchandiseTable.execute(EmbeddedDatabaseConstants.CreateMerchandiseTable);

            Statement createCarTable = conn.createStatement();
            createCarTable.execute(EmbeddedDatabaseConstants.CreateCarTable);

            Statement createUtilityVehicleTable = conn.createStatement();
            createUtilityVehicleTable.execute(EmbeddedDatabaseConstants.CreateUtilityVehicleTable);

            conn.commit();
        }
        catch(Exception ex){
            System.out.println("in connection" + ex);
        }

        closeDb();
    }

    private static void dropTables(){
        try {
            Driver derbyEmbeddedDriver = new EmbeddedDriver();
            DriverManager.registerDriver(derbyEmbeddedDriver);
            conn = DriverManager.getConnection(EmbeddedDatabaseConstants.ConnString);
            conn.setAutoCommit(false);

            Statement dropPf = conn.createStatement();
            dropPf.execute("drop table pf");

            Statement dropPj = conn.createStatement();
            dropPj.execute("drop table pj");

            Statement dropManager = conn.createStatement();
            dropManager.execute("drop table manager");

            Statement dropMechanic = conn.createStatement();
            dropMechanic.execute("drop table mechanic");

            Statement dropSalesman = conn.createStatement();
            dropSalesman.execute("drop table salesman");

            Statement dropMerchandise = conn.createStatement();
            dropMerchandise.execute("drop table merchandise");

            Statement dropCar = conn.createStatement();
            dropCar.execute("drop table car");

            Statement dropUtilityVehicle = conn.createStatement();
            dropUtilityVehicle.execute("drop table utilityVehicle");

            conn.commit();
        }
        catch(Exception ex){
            System.err.println("Exception - " + ex);
        }
    }

    public static void closeDb(){
        try {
            DriverManager.getConnection
                    ("jdbc:derby:;shutdown=true");
        } catch (SQLException ex) {
            if (((ex.getErrorCode() == 50000) &&
                    ("XJ015".equals(ex.getSQLState())))) {
                System.out.println("\nDatabase has shut down normally.");
            } else {
                //System.err.println("Derby did not shut down normally");
                System.err.println(ex.getMessage());
            }
        }
    }
}
