package services;

import models.accounts.CreditAccount;
import utilities.jdbc.JDBCService;
import utilities.jdbc.JDBCServiceInterface;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class CreditAccountService implements JDBCServiceInterface<CreditAccount> {
    private static CreditAccountService instance = null;

    public static CreditAccountService getInstance() {
        if (instance == null)
        {
            instance = new CreditAccountService();
        }
        return instance;
    }

    @Override
    public CreditAccount get(int id) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM creditAccounts WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(sql);
        prep.setInt(1, id);

        prep.execute();
        prep.getResultSet().next();

        return new CreditAccount(prep.getResultSet());
    }

    @Override
    public List<CreditAccount> getAll() throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String sql = "SELECT * FROM creditAccounts";

        ResultSet rs = jdbcService.getStatement().executeQuery(sql);
        var records = new ArrayList<CreditAccount>();

        while(rs.next()) {
            var record = new CreditAccount(rs);
            records.add(record);
        }

        return records;
    }

    @Override
    public void add(CreditAccount creditAccount) throws SQLException {
        var jdbcService = JDBCService.getInstance();
        String query = "INSERT INTO creditAccounts (bank, amount, currency, customerId, amountInDepth) VALUES (?, ?, ?, ?, ?)";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, creditAccount.getBank());
        prep.setFloat(2, creditAccount.getAmount());
        prep.setString(3, creditAccount.getCurrency());
        prep.setInt(4, creditAccount.getCustomerId());
        prep.setFloat(5, creditAccount.getAmountInDepth());

        prep.execute();
        prep.close();
    }

    @Override
    public void update(CreditAccount creditAccount) throws SQLException {
        get(creditAccount.getId());
        var jdbcService = JDBCService.getInstance();
        String query = "UPDATE creditAccounts SET bank = ?, amount = ?, currency = ?, customerId = ?, amountInDepth = ? WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setString(1, creditAccount.getBank());
        prep.setFloat(2, creditAccount.getAmount());
        prep.setString(3, creditAccount.getCurrency());
        prep.setInt(4, creditAccount.getCustomerId());
        prep.setFloat(5, creditAccount.getAmountInDepth());
        prep.setInt(6, creditAccount.getId());

        prep.executeUpdate();
        prep.close();
    }

    @Override
    public void delete(int id) throws SQLException {
        get(id);
        var jdbcService = JDBCService.getInstance();
        String query = "DELETE FROM creditAccounts WHERE id = ?";

        PreparedStatement prep = jdbcService.getConnection().prepareStatement(query);
        prep.setInt(1, id);

        prep.execute();
        prep.close();
    }
}

