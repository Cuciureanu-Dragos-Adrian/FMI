package collections;

import interfaces.hasId;
import interfaces.persistentWithDb;

/** CustomCollection that performs a sort on the list after every insert
 *
 */
public abstract class CustomSortedCollection<T extends hasId & Comparable<T> & persistentWithDb> extends CustomCollection<T>{
    /** Insert object into list. Sorts the list after every insert.
     *
     * @param object the object to be inserted
     * @throws Exception if the object's id already exists.
     */
    @Override
    public void add(T object) throws Exception {
        super.add(object);
        this.objectList.sort(T::compareTo);
    }

    @Override
    public void readFromDb() throws Exception {
        this.objectList.sort(T::compareTo);
    }
}
