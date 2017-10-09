package ReadXML;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Created by wengwei on 17-6-16.
 */
public class XmlByDom implements XmlDocument{
    private Document document;
    @Override
    public void parserXml(String FileName) {
        try {
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document document = db.parse(FileName);
            NodeList users = document.getChildNodes();
            //获得元素
            for (int i = 0; i < users.getLength(); ++i) {
//                System.out.println(users.item(i).getTextContent());
                Node user = users.item(i);
                NodeList userInfo = user.getChildNodes();
                //遍历元素特征
                for (int j = 0; j < userInfo.getLength(); ++j) {
                    Node node = userInfo.item(j);
                    NodeList userMeta = node.getChildNodes();
                    //打印每个特征的值
                    for (int k = 0; k < userMeta.getLength(); k++) {
                        if (userMeta.item(k).getNodeName() != "#text") {
                            System.out.println(userMeta.item(k).getNodeName() + ":" + userMeta.item(k).getTextContent());
                        }
//                        System.out.println(userMeta.item(k).getNodeName() + ":" + userMeta.item(k).getTextContent());
                        System.out.println();
                    }
                }
            }
        }catch (FileNotFoundException e){
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
