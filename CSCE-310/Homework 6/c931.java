import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;


public class c931
{
    public static void main(String [] args){
        Connection conn = null;
        try
        {
        Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
        conn = DriverManager.getConnection("jdbc:derby://localhost:1527/manfDB2");
        System.out.println ("\n---Database connection established---\n");

        Scanner sc = new Scanner(System.in);
        System.out.print("Please input the manufacturer: ");
        String manf = sc.nextLine();

        Statement st = conn.createStatement();
        ResultSet rs = st.executeQuery("select product.model, product.type, pc.speed, pc.ram, pc.hd, pc.price from product,pc where maker = '" + manf + "' and product.model = pc.model");
        ResultSetMetaData rsmd = rs.getMetaData();
        
        int columnsNumber = rsmd.getColumnCount();

        while (rs.next()) {      
            for(int i = 1 ; i <= columnsNumber; i++)
                System.out.print(rs.getString(i) + " ");

            System.out.println();         
        }

        rs = st.executeQuery("select product.model, product.type, laptop.speed, laptop.ram, laptop.hd, laptop.screen, laptop.price from product,laptop where maker = '" + manf + "' and product.model = laptop.model");
        rsmd = rs.getMetaData();
        
        columnsNumber = rsmd.getColumnCount();

        while (rs.next()) {        
            for(int i = 1 ; i <= columnsNumber; i++)
                System.out.print(rs.getString(i) + " "); 

            System.out.println();        
        }

        rs = st.executeQuery("select product.model, product.type, printer.color, printer.type, printer.price from product,printer where maker = '" + manf + "' and product.model = printer.model");
        rsmd = rs.getMetaData();
        
        columnsNumber = rsmd.getColumnCount();

        while (rs.next()) {      
            for(int i = 1 ; i <= columnsNumber; i++)
                System.out.print(rs.getString(i) + " "); 

            System.out.println();          
        }

        }
        catch (Exception e)
        {
        System.out.println("Connection Issue: " + e.getMessage());
        }
    }
}