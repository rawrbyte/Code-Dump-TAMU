package simpledb.parse;

/**
 * Data for the SQL <i>create table</i> statement.
 * @author Edward Sciore
 */
public class DropTableData {
   private String tblname;
   
   /**
    * Saves the table name and schema.
    */
   public DropTableData(String tblname) {
      this.tblname = tblname;
   }
   
   /**
    * Returns the name of the new table.
    * @return the name of the new table
    */
   public String tableName() {
      return tblname;
   }
}

