package utilities.jdbc;

import java.sql.SQLException;
import java.util.List;

public interface JDBCServiceInterface<Template> {
    Template get(int id) throws SQLException;

    List<Template> getAll() throws SQLException;

    void add(Template record) throws SQLException;

    void update(Template record) throws SQLException;

    void delete(int id) throws SQLException;
}