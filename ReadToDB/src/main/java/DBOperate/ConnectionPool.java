package DBOperate;

import java.sql.Connection;
import java.sql.SQLException;
import java.util.Vector;

public class ConnectionPool {
	private Vector<Connection> pool;
	private int poolSize = 12;
	final String driverName = "com.mysql.jdbc.Driver"; 
	final String dbURL = "jdbc:mysql://localhost:3306/xmldb?useSSL=false";
	final String userName = "root";
	final String userPwd = "123";
	private static ConnectionPool instance = null;
	private ConnectionPool(){
		init();
	}
	private void init(){
		pool = new Vector<Connection>(poolSize);
		addConnection();
	}
	
	public synchronized void release(Connection coon){
		pool.add(coon);
	}
	public synchronized void closePool(){
		for(int i = 0; i < pool.size(); i++) {
	      try {
			((Connection)pool.get(i)).close();
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	      pool.remove(i);
		}
	}
	public static ConnectionPool getInstance(){
		if(instance == null){
			instance = new ConnectionPool(); 
		}
		return instance;
	}
	public synchronized Connection getConnection(){
		if(pool.size() >0){
			Connection conn = pool.get(0);
			pool.remove(conn);
			return conn;
		}else{
			addConnection();
			Connection conn = pool.get(0);
			pool.remove(conn);
			return conn;
		}
	}
	private void addConnection(){
		Connection coon = null;
		for(int i=0;i<poolSize;i++){
			try {
				Class.forName(driverName);
				coon = java.sql.DriverManager.getConnection(dbURL, userName, userPwd);
				pool.add(coon);
			} catch (ClassNotFoundException | SQLException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}
