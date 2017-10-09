package DBclass;

import java.math.BigDecimal;
import java.sql.Timestamp;

/**
 * Created by wengwei on 17-6-9.
 */
public class InfoM {
    public InfoM(){}

    @Override
    public String toString() {
        return "InfoM{" +
                "id=" + id +
                ", appName='" + appName + '\'' +
                ", totalSourceBytes=" + totalSourceBytes +
                ", totalDestinationBytes=" + totalDestinationBytes +
                ", totalDestinationPackets=" + totalDestinationPackets +
                ", totalSourcePackets=" + totalSourcePackets +
                ", sourcePayloadAsBase64='" + sourcePayloadAsBase64 + '\'' +
                ", sourcePayloadAsUTF='" + sourcePayloadAsUTF + '\'' +
                ", destinationPayloadAsBase64='" + destinationPayloadAsBase64 + '\'' +
                ", destinationPayloadAsUTF='" + destinationPayloadAsUTF + '\'' +
                ", direction='" + direction + '\'' +
                ", sourceTCPFlagsDescription='" + sourceTCPFlagsDescription + '\'' +
                ", destinationTCPFlagsDescription='" + destinationTCPFlagsDescription + '\'' +
                ", source='" + source + '\'' +
                ", protocolName='" + protocolName + '\'' +
                ", sourcePort=" + sourcePort +
                ", destination='" + destination + '\'' +
                ", destinationPort=" + destinationPort +
                ", startDateTime=" + startDateTime +
                ", stopDateTime=" + stopDateTime +
                ", Tag='" + Tag + '\'' +
                '}';
    }

    public BigDecimal getId() {
        return id;
    }

    public void setId(BigDecimal id) {
        this.id = id;
    }

    public String getAppName() {
        return appName;
    }

    public void setAppName(String appName) {
        this.appName = appName;
    }

    public BigDecimal getTotalSourceBytes() {
        return totalSourceBytes;
    }

    public void setTotalSourceBytes(BigDecimal totalSourceBytes) {
        this.totalSourceBytes = totalSourceBytes;
    }

    public BigDecimal getTotalDestinationBytes() {
        return totalDestinationBytes;
    }

    public void setTotalDestinationBytes(BigDecimal totalDestinationBytes) {
        this.totalDestinationBytes = totalDestinationBytes;
    }

    public BigDecimal getTotalDestinationPackets() {
        return totalDestinationPackets;
    }

    public void setTotalDestinationPackets(BigDecimal totalDestinationPackets) {
        this.totalDestinationPackets = totalDestinationPackets;
    }

    public BigDecimal getTotalSourcePackets() {
        return totalSourcePackets;
    }

    public void setTotalSourcePackets(BigDecimal totalSourcePackets) {
        this.totalSourcePackets = totalSourcePackets;
    }

    public String getSourcePayloadAsBase64() {
        return sourcePayloadAsBase64;
    }

    public void setSourcePayloadAsBase64(String sourcePayloadAsBase64) {
        this.sourcePayloadAsBase64 = sourcePayloadAsBase64;
    }

    public String getSourcePayloadAsUTF() {
        return sourcePayloadAsUTF;
    }

    public void setSourcePayloadAsUTF(String sourcePayloadAsUTF) {
        this.sourcePayloadAsUTF = sourcePayloadAsUTF;
    }

    public String getDestinationPayloadAsBase64() {
        return destinationPayloadAsBase64;
    }

    public void setDestinationPayloadAsBase64(String destinationPayloadAsBase64) {
        this.destinationPayloadAsBase64 = destinationPayloadAsBase64;
    }

    public String getDestinationPayloadAsUTF() {
        return destinationPayloadAsUTF;
    }

    public void setDestinationPayloadAsUTF(String destinationPayloadAsUTF) {
        this.destinationPayloadAsUTF = destinationPayloadAsUTF;
    }

    public String getDirection() {
        return direction;
    }

    public void setDirection(String direction) {
        this.direction = direction;
    }

    public String getSourceTCPFlagsDescription() {
        return sourceTCPFlagsDescription;
    }

    public void setSourceTCPFlagsDescription(String sourceTCPFlagsDescription) {
        this.sourceTCPFlagsDescription = sourceTCPFlagsDescription;
    }

    public String getDestinationTCPFlagsDescription() {
        return destinationTCPFlagsDescription;
    }

    public void setDestinationTCPFlagsDescription(String destinationTCPFlagsDescription) {
        this.destinationTCPFlagsDescription = destinationTCPFlagsDescription;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getProtocolName() {
        return protocolName;
    }

    public void setProtocolName(String protocolName) {
        this.protocolName = protocolName;
    }

    public BigDecimal getSourcePort() {
        return sourcePort;
    }

    public void setSourcePort(BigDecimal sourcePort) {
        this.sourcePort = sourcePort;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public BigDecimal getDestinationPort() {
        return destinationPort;
    }

    public void setDestinationPort(BigDecimal destinationPort) {
        this.destinationPort = destinationPort;
    }

    public Timestamp getStartDateTime() {
        return startDateTime;
    }

    public void setStartDateTime(Timestamp startDateTime) {
        this.startDateTime = startDateTime;
    }

    public Timestamp getStopDateTime() {
        return stopDateTime;
    }

    public void setStopDateTime(Timestamp stopDateTime) {
        this.stopDateTime = stopDateTime;
    }

    public String getTag() {
        return Tag;
    }

    public void setTag(String tag) {
        Tag = tag;
    }

    private BigDecimal id;
    private String appName;
    private BigDecimal totalSourceBytes;
    private BigDecimal totalDestinationBytes;
    private BigDecimal totalDestinationPackets;
    private BigDecimal totalSourcePackets;
    private String sourcePayloadAsBase64;
    private String sourcePayloadAsUTF;
    private String destinationPayloadAsBase64;
    private String destinationPayloadAsUTF;
    private String direction;
    private String sourceTCPFlagsDescription;
    private String destinationTCPFlagsDescription;
    private String source;
    private String protocolName;
    private BigDecimal sourcePort;
    private String destination;
    private BigDecimal destinationPort;
    private Timestamp startDateTime;
    private Timestamp stopDateTime;
    private String Tag;
}