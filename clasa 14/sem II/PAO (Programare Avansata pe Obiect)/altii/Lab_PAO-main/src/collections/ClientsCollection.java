package collections;

import database.DatabaseReadService;
import models.clients.Client;

import java.util.List;

public class ClientsCollection extends CustomSortedCollection<Client> {

    private static ClientsCollection object = null;

    private ClientsCollection(){
        super();
    }

    /** Factory method for the singleton class
     *
     * @return the singleton instance of this class
     */
    public static ClientsCollection getCollection() {
        if(object == null)
            object = new ClientsCollection();
        return object;
    }

    @Override
    public void readFromDb() throws Exception {
        List<Client> pfs = DatabaseReadService.readPFs();
        List<Client> pjs = DatabaseReadService.readPJs();

        this.objectList.addAll(pfs); //add objects to list
        this.objectIds.addAll(pfs.stream().map(Client::getId).toList()); //add ids to id set

        this.objectList.addAll(pjs);
        this.objectIds.addAll(pjs.stream().map(Client::getId).toList());

        super.readFromDb();
    }

}
