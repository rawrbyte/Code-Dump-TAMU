import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;


public class d942{
    
    public static void main(String [] args){
        Connection conn = null;
        try
        {
        Class.forName("org.apache.derby.jdbc.ClientDriver").newInstance();
        conn = DriverManager.getConnection("jdbc:derby://localhost:1527/manfDB2");
        System.out.println ("\n---Database connection established---\n");

        Scanner sc = new Scanner(System.in);
        System.out.print("Price: ");
        String price = sc.nextLine();


        PreparedStatement ps = conn.prepareStatement("select product.type, count(*) from product,pc where price > ? and product.model = pc.model group by type");

        ps.setString(1, price);
        ResultSet rs = ps.executeQuery();
        ResultSetMetaData rsmd = rs.getMetaData();
        
        int columnsNumber = rsmd.getColumnCount();

        while (rs.next()) {    
            for(int i = 1 ; i <= columnsNumber; i++)
                System.out.print(rs.getString(i) + " ");

            System.out.println();         
        }

        ps = conn.prepareStatement("select product.type, count(*) from product,laptop where price > ? and product.model = laptop.model group by type");
        
        ps.setString(1, price);
        rs = ps.executeQuery();
        rsmd = rs.getMetaData();
        
        columnsNumber = rsmd.getColumnCount();

        while (rs.next()) {
            for(int i = 1 ; i <= columnsNumber; i++)
                System.out.print(rs.getString(i) + " ");

            System.out.println();         
        }

        ps = conn.prepareStatement("select product.type, count(*) from product,printer where price > ? and product.model = printer.model group by product.type");
        
        ps.setString(1, price);
        rs = ps.executeQuery();
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