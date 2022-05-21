package utilities.jdbc;

import java.sql.*;

public class JDBCService {
    private JDBCService() {}
    private static JDBCService instance = null;
    private static Connection connection;
    private static Statement statement;

    public static JDBCService getInstance() {
        if(instance == null)
        {
            instance = new JDBCService();

            String address = "jdbc:mysql://localhost:3306/";
            String db = "bankdb";
            String username = "root";
            String password = "password";

            try {
                connection = DriverManager.getConnection(address + db, username, password);
                statement = connection.createStatement();

                instance.createDatabase(db);

                instance.createTableManagers();
                instance.createTableBankers();
                instance.createTableCustomers();
                instance.createTableCreditAccounts();
                instance.createTableDebitAccounts();
                instance.createTableTransactions();

            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
        return instance;
    }


    public Statement getStatement() {
        return statement;
    }

    public Connection getConnection() {
        return connection;
    }


    private void createDatabase(String db) throws SQLException {
        getStatement().execute("CREATE DATABASE IF NOT EXISTS " + db);
    }

    private void createTableManagers() throws SQLException {
        String sql =
            "CREATE TABLE IF NOT EXISTS managers (" +
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
            "salary FLOAT(10) NOT NULL," +
            "firstName VARCHAR(20)," +
            "lastName VARCHAR(20)," +
            "bonus FLOAT(10) NOT NULL)";
        getStatement().execute(sql);
    }

    private void createTableBankers() throws SQLException {
        String sql =
            "CREATE TABLE IF NOT EXISTS bankers (" +
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
            "salary FLOAT(10) NOT NULL," +
            "firstName VARCHAR(20)," +
            "lastName VARCHAR(20)," +
            "workedFreeDays FLOAT(10) NOT NULL)";
        getStatement().execute(sql);
    }

    private void createTableCustomers() throws SQLException {
        String sql =
            "CREATE TABLE IF NOT EXISTS customers (" +
            "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
            "firstName VARCHAR(20)," +
            "lastName VARCHAR(20)," +
            "email VARCHAR(30) NOT NULL)";
        getStatement().execute(sql);
    }

    private void createTableCreditAccounts() throws SQLException {
        String sql =
                "CREATE TABLE IF NOT EXISTS creditAccounts (" +
                        "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
                        "bank VARCHAR(20)," +
                        "amount FLOAT(10) NOT NULL," +
                        "currency VARCHAR(20)," +
                        "customerId INT," +
                        "amountInDepth FLOAT(10) NOT NULL," +
                        "FOREIGN KEY (customerId) REFERENCES customers (id) ON DELETE CASCADE)";
        getStatement().execute(sql);
    }

    private void createTableDebitAccounts() throws SQLException {
        String sql =
                "CREATE TABLE IF NOT EXISTS debitAccounts (" +
                        "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
                        "bank VARCHAR(20)," +
                        "amount FLOAT(10) NOT NULL," +
                        "currency VARCHAR(20)," +
                        "customerId INT," +
                        "interestRate FLOAT(10) NOT NULL," +
                        "FOREIGN KEY (customerId) REFERENCES customers (id) ON DELETE CASCADE)";
        getStatement().execute(sql);
    }

    private void createTableTransactions() throws SQLException {
        String sql =
                "CREATE TABLE IF NOT EXISTS transactions (" +
                        "id INT NOT NULL AUTO_INCREMENT PRIMARY KEY," +
                        "senderId INT," +
                        "receiverId INT," +
                        "amount FLOAT(10) NOT NULL," +
                        "commission FLOAT(10) NOT NULL," +
                        "FOREIGN KEY (senderId) REFERENCES creditAccounts (id) ON DELETE CASCADE," +
                        "FOREIGN KEY (receiverId) REFERENCES creditAccounts (id) ON DELETE CASCADE)";
        getStatement().execute(sql);
    }
}