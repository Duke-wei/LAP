package Main;

import DBOperate.ConnectionPool;
import DBOperate.WriteXMLDB;
import DBclass.InfoM;
import org.dom4j.DocumentException;
import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

import java.io.File;
import java.math.BigDecimal;
import java.sql.Timestamp;
import java.util.Iterator;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingDeque;
import java.util.concurrent.TimeUnit;

/**
 * Created by wengwei on 17-6-9.
 */
public class Readxml implements Runnable{
    private String FileName;
    private final BlockingQueue<InfoM> blockingQueue;
    public Readxml(String FileName){
        this.FileName = FileName;
        blockingQueue = new LinkedBlockingDeque<InfoM>(5);
    }
    public Readxml(String FileName,BlockingQueue<InfoM> blockingQueue){
       this.FileName = FileName;
       this.blockingQueue = blockingQueue;
    }
    private static InfoM GetInfom(Element element){
        InfoM inf = new InfoM();
        inf.setAppName(element.elementText("appName"));
        inf.setTotalSourceBytes(BigDecimal.valueOf(Long.parseLong(element.elementText("totalSourceBytes"))));
        inf.setTotalDestinationBytes(BigDecimal.valueOf(Long.parseLong(element.elementText("totalDestinationBytes"))));
        inf.setTotalDestinationPackets(BigDecimal.valueOf(Long.parseLong(element.elementText("totalDestinationPackets"))));
        inf.setTotalSourcePackets(BigDecimal.valueOf(Long.parseLong(element.elementText("totalSourcePackets"))));
        String SPL = element.elementText("sourcePayloadAsBase64");
        if(SPL!=null&&SPL.length()>1200){
            inf.setSourcePayloadAsBase64(SPL.substring(0,1200));
        }else{
            inf.setSourcePayloadAsBase64(SPL);
        }
        String SPL2 = element.elementText("sourcePayloadAsUTF");
        if(SPL2!=null&&SPL2.length()>1200) {
            inf.setSourcePayloadAsUTF(SPL2.substring(0, 1200));
        }else{
            inf.setSourcePayloadAsUTF(SPL2);
        }
        String DPL = element.elementText("destinationPayloadAsBase64");
        if(DPL!=null&&DPL.length()>1200) {
            inf.setDestinationPayloadAsBase64(DPL.substring(0, 1200));
        }else{
            inf.setDestinationPayloadAsBase64(DPL);
        }
        String DPL2 = element.elementText("destinationPayloadAsUTF");
        if(DPL2!=null&&DPL2.length()>1200) {
            inf.setDestinationPayloadAsUTF(DPL2.substring(0, 1200));
        }else{
            inf.setDestinationPayloadAsUTF(DPL2);
        }
        inf.setDirection(element.elementText("direction"));
        inf.setSourceTCPFlagsDescription(element.elementText("sourceTCPFlagsDescription"));
        inf.setDestinationTCPFlagsDescription(element.elementText("destinationTCPFlagsDescription"));
        inf.setSource(element.elementText("source"));
        inf.setProtocolName(element.elementText("protocolName"));
        inf.setSourcePort(BigDecimal.valueOf(Long.parseLong(element.elementText("sourcePort"))));
        inf.setDestination(element.elementText("destination"));
        inf.setDestinationPort(BigDecimal.valueOf(Long.parseLong(element.elementText("destinationPort"))));
        inf.setStartDateTime(Timestamp.valueOf(element.elementText("startDateTime").replace('T',' ')));
        inf.setStopDateTime(Timestamp.valueOf(element.elementText("stopDateTime").replace('T',' ')));
        inf.setTag(element.elementText("Tag"));
        return inf;
    }

    public void testRead(){
        SAXReader reader = new SAXReader();
        Document document = null;
        try {
            document = reader.read(new File(FileName));
            Element root = document.getRootElement();
            Iterator it = root.elementIterator();
            while(it.hasNext()){
                Element element = (Element) it.next();
//                InfoM inf = GetInfom(element);
//                System.out.println(inf);
                Iterator eleit = element.elementIterator();
                while(eleit.hasNext()){
                    Element e = (Element) eleit.next();
                    System.out.println(e.getName()+":"+e.getText());
                }
            }
        } catch (DocumentException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {
        SAXReader reader = new SAXReader();
        Document document = null;
        try {
            document = reader.read(new File(FileName));
            Element root = document.getRootElement();
            Iterator it = root.elementIterator();
            while(it.hasNext()){
                Element element = (Element) it.next();
                /*
                Iterator attrlt = element.attributeIterator();
                while(attrlt.hasNext()){
                    Attribute a = (Attribute)attrlt.next();
                    System.out.println(a.getValue());
                }
                 */
                /*
                Iterator eleit = element.elementIterator();
                while(eleit.hasNext()){
                    Element e = (Element) eleit.next();
                    System.out.println(e.getName()+":"+e.getText());
                }
                */
                InfoM inf = GetInfom(element);
                //blockingQueue.add(inf);
                blockingQueue.put(inf);
                //System.out.println(inf);
            }
        } catch (DocumentException e) {
            e.printStackTrace();
        }catch (InterruptedException e1){
           System.out.println("blockingQueue full");
        }
    }
    public static void main(String[] args){
        boolean stop = false;
        BlockingQueue<InfoM> blockingQueue = new LinkedBlockingDeque<InfoM>(100);
        ConnectionPool coon = ConnectionPool.getInstance();
        Readxml producer = new Readxml("Resources/T22.xml",blockingQueue);
        Consumer consumer = new Consumer(blockingQueue,coon);
        Thread pro = new Thread(producer);
        pro.start();
        try{
            TimeUnit.SECONDS.sleep(5);
        } catch (InterruptedException e) {
            System.out.println("produce run first 5s");
        }
        Thread con1 = new Thread(consumer); con1.start();
        Thread con2 = new Thread(consumer); con2.start();
        Thread con3 = new Thread(consumer); con3.start();
        Thread con4 = new Thread(consumer); con4.start();
        Thread con5 = new Thread(consumer); con5.start();
        while(!stop) {
            try{
                //Thread.sleep(1000);
                TimeUnit.SECONDS.sleep(12);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
            if (!pro.isAlive() && blockingQueue.isEmpty()) {
                con1.interrupt();
                con2.interrupt();
                con3.interrupt();
                con4.interrupt();
                con5.interrupt();
                coon.closePool();
                stop = true;
            }
        }
        System.out.println("OK,OVER");
    }
}

class Consumer implements Runnable{
    private final BlockingQueue<InfoM> blockingQueue;
    private final ConnectionPool coon;
    public Consumer(BlockingQueue<InfoM> blockingQueue,ConnectionPool coon){
        this.coon = coon;
        this.blockingQueue = blockingQueue;
    }
    @Override
    public void run() {
       while(!Thread.currentThread().isInterrupted()){
           InfoM inf;
           try {
               //inf = blockingQueue.take();
               inf = blockingQueue.poll(3, TimeUnit.SECONDS);
               if(inf==null) continue;
               WriteXMLDB.WriteOneBackToXMLDB(coon, inf);
               //save to xmlDB
           } catch (InterruptedException e) {
               //reset interrupt
               Thread.currentThread().interrupt();
           }
       }
    }
}
