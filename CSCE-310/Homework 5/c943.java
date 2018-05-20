import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.*;

public class c943
{
	
	public static void main(String [] args){
		String DBLocation = "database-new.cse.tamu.edu"; //The host 
		String DBname = ""; //Generally your CS username or username-text like explained above
		String DBUser = ""; //CS username
		String DBPass = ""; //password setup via CSNet for the MySQL database
		String className = "", type = "", country = "", numGuns = "", bore = "", displacement = "";
		
		Connection conn = null;
		try
		{
		Scanner sc = new Scanner(System.in);	
		System.out.print("Username: ");
		DBUser = sc.nextLine();
		System.out.print("Password: ");
		DBPass = sc.nextLine();
		System.out.print("Database: ");
		DBname = sc.nextLine();
			
		String connectionString = "jdbc:mysql://"+DBLocation+"/"+DBname;
		Class.forName ("com.mysql.jdbc.Driver").newInstance();
		conn = DriverManager.getConnection(connectionString, DBUser, DBPass);
		System.out.println ("\n---Database connection established---\n");
		

        System.out.println("Please input the attributes in their respective order: class, type, country, numGuns, bore, displacement.");
        System.out.print("Class: ");
        className = sc.nextLine();
        System.out.print("Type: ");
		type = sc.nextLine();
		System.out.print("Country: ");
		country = sc.nextLine();
		System.out.print("numGuns: ");
		numGuns = sc.nextLine();
		System.out.print("Bore: ");
		bore = sc.nextLine();
		System.out.print("Displacement: ");
		displacement = sc.nextLine();


		Statement st = conn.createStatement();
        String procedure = "create procedure classShip(IN class varchar(20), in type char(20), in numGuns int, in bore int, in displacement int) insert into classes values (class, type, country, numGuns, bore, displacement)";
        st.executeUpdate(procedure);

        st.executeUpdate("call classShip("+className+","+type+","+country+","+numGuns+","+bore+","+displacement+")");

		}
		catch (Exception e)
		{
		System.out.println("Connection Issue: " + e.getMessage());
		}
	}
}