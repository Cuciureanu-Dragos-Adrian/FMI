package services;

import models.accounts.CreditAccount;
import models.accounts.DebitAccount;
import models.customers.Customer;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class CustomerService implements JDBCServiceInterface<Customer> {
    private static CustomerService instance = null;

    public static CustomerService getInstance() {
        if (instance == null)
        {
            instance = new CustomerService();
        }
        return instance;
    }

    @Override
    public Customer get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM customers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new Customer(prep.getResultSet());
    }

    @Override
    public List<Customer> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM customers";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<Customer>();

        while(rs.next()) {
            var record = new Customer(rs);
            records.add(record);
        }

        return records;
    }

    public List<CreditAccount> getCreditAccountOfCustomer(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM creditAccounts WHERE customerId = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        ResultSet rs = prep.getResultSet();
        var records = new ArrayList<CreditAccount>();

        while(rs.next()) {
            var record = new CreditAccount(rs);
            records.add(record);
        }

        return records;
    }

    public List<DebitAccount> getDebitAccountOfCustomer(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM debitAccounts WHERE customerId = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        ResultSet rs = prep.getResultSet();
        var records = new ArrayList<DebitAccount>();

        while(rs.next()) {
            var record = new DebitAccount(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(Customer customer) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO customers (firstName, lastName, email) VALUES (?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, customer.getFirstName());
        prep.setString(2, customer.getLastName());
        prep.setString(3, customer.getEmail());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(Customer customer) throws SQLException {
        get(customer.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE customers SET firstName = ?, lastName = ?, email = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, customer.getFirstName());
        prep.setString(2, customer.getLastName());
        prep.setString(3, customer.getEmail());
        prep.setInt(4, customer.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM customers WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}
