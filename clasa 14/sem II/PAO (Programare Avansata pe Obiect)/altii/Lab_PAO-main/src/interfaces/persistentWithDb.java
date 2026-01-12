package interfaces;

import java.sql.SQLException;

public interface persistentWithDb{

    /** Creates SQL insert statement and runs it from EmbeddedDatabaseService
     *
     */
    void saveToDb() throws SQLException;

    /** Creates SQL update statement and runs it from EmbeddedDatabaseService
     *
     */
    void updateInDb() throws SQLException;

    /** Creates SQL delete statement and runs it from EmbeddedDatabaseService
     *
     */
    void deleteFromDb() throws SQLException;
}
