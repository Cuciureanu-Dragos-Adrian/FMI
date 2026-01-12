package main;
import database.EmbeddedDatabaseService;
import services.MenuService;

public class Main {
    public static void main(String[] args) throws Exception {
        EmbeddedDatabaseService.initDb(); // make sure database is created and initiate the connection
        MenuService.runMenu();
        EmbeddedDatabaseService.closeDb(); // close database
        //TODO - check sorts
    }
}