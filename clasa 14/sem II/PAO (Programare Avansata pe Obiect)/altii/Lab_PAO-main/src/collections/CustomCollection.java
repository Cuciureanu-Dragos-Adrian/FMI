package collections;

import interfaces.hasId;
import interfaces.persistentWithDb;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

/** Singleton class template used in storing object list information.
 *
 */
public abstract class CustomCollection<T extends hasId & persistentWithDb> {

    protected List<T> objectList;
    protected Set<String> objectIds;
    protected CustomCollection() {
        this.objectList = new ArrayList<>();
        this.objectIds = new HashSet<>();
    }
    public List<T> getList(){
        return objectList;
    }

    /** Gets an element by a given Id;
     *
     * @return the object with required id or null if it does not exist
     * @throws Exception if 2 elements with the same id exist
     */
    public T getElementById(String id) throws Exception {
        List<T> objects = this.objectList.stream().filter((x) -> x.getId().equals(id)).toList();

        if(objects.size() == 0)
            return null;
        if(objects.size() > 1)
            throw new Exception("Duplicate id in clients collection!");

        return objects.get(0);
    }

    /** Checks if an object with the given id exists.
     *
     * @return (bool) whether the object exists
     */
    public boolean idExists(String id){
        return this.objectIds.contains(id);
    }

    /** Adds an object to the collection.
     *
     * @param object the object to be inserted
     * @throws Exception if the given id already exists
     */
    public void add(T object) throws Exception {
        String id = object.getId();

        if(idExists(id))
            throw new Exception("Object with given id already exists");

        objectList.add(object);
        objectIds.add(id);
        object.saveToDb();
    }

    /** Removes an object from the collection
     *
     * @param id the id of the object to be removed
     * @throws Exception if the object does not exist.
     */
    public void delete(String id) throws Exception {
        if(!idExists(id))
            throw new Exception("Object with given id does not exist");
        T object = getElementById(id);

        objectIds.remove(id);
        objectList.remove(getElementById(id));
        object.deleteFromDb();
    }

    /** Updates an object with a given id
     *
     * @param object the modified object
     * @throws Exception if the object does not exist
     */
    public void update(T object) throws Exception {
        String id = object.getId();

        if(!idExists(id))
            throw new Exception("Id does not exist!");

        for(int index = 0; index < objectList.size(); index++)
            if(objectList.get(index).getId().equals(id)) {
                objectList.set(index, object);
                object.updateInDb();
            }
    }

    public abstract void readFromDb() throws Exception;
}
