package DBOperate;

import DBclass.InfoM;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

/**
 * Created by wengwei on 17-6-9.
 */
public class WriteXMLDB {
    public static void WriteOneBackToXMLDB(ConnectionPool coon,InfoM inf) {
        String writesql = "INSERT INTO InfoM(appName,totalSourceBytes,totalDestinationBytes,totalDestinationPackets,totalSourcePackets,sourcePayloadAsBase64,sourcePayloadAsUTF,destinationPayloadAsBase64,destinationPayloadAsUTF,direction,sourceTCPFlagsDescription,destinationTCPFlagsDescription,source,protocolName,sourcePort,destination,destinationPort,startDateTime,stopDateTime,Tag) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
        Connection con = coon.getConnection();
        try{
            con.setAutoCommit(false);
            PreparedStatement ps = con.prepareStatement(writesql);
            ps.setString(1,inf.getAppName());
            ps.setBigDecimal(2,inf.getTotalSourceBytes());
            ps.setBigDecimal(3,inf.getTotalDestinationBytes());
            ps.setBigDecimal(4,inf.getTotalDestinationPackets());
            ps.setBigDecimal(5,inf.getTotalSourcePackets());
            ps.setString(6,inf.getSourcePayloadAsBase64());
            ps.setString(7,inf.getSourcePayloadAsUTF());
            ps.setString(8,inf.getDestinationPayloadAsBase64());
            ps.setString(9,inf.getDestinationPayloadAsUTF());
            ps.setString(10,inf.getDirection());
            ps.setString(11,inf.getSourceTCPFlagsDescription());
            ps.setString(12,inf.getDestinationTCPFlagsDescription());
            ps.setString(13,inf.getSource());
            ps.setString(14,inf.getProtocolName());
            ps.setBigDecimal(15,inf.getSourcePort());
            ps.setString(16,inf.getDestination());
            ps.setBigDecimal(17,inf.getDestinationPort());
            ps.setTimestamp(18,inf.getStartDateTime());
            ps.setTimestamp(19,inf.getStopDateTime());
            ps.setString(20,inf.getTag());
            ps.execute();
            ps.close();
            con.commit();
        }catch (Exception e){
            try{
                con.rollback();
            }catch (SQLException e1){
                e1.printStackTrace();
            }
            e.printStackTrace();
        }finally {
            coon.release(con);
        }
    }
}
