import argparse
import sys
import os
import rospy
import rosbag

if __name__ == '__main__':
    print 1
    # parse command line
    parser = argparse.ArgumentParser(description='''bag file to txt file''')
    parser.add_argument('inputbag', help='input bag file')
    parser.add_argument('outputtxt', help='out text file')
    args = parser.parse_args()

    print "Processing bag file:"
    print "  in:",args.inputbag
    print "  out:",args.outputtxt

    inbag = rosbag.Bag(args.inputbag,'r')
    outtxt = open(args.outputtxt,'w')
    # outtxt.write('# text file for '+ args.inputbag + '\n# format: time stamp x y z qx qy qz qw\n')

    for topic, msg, t in inbag.read_messages():
        if topic == "/zed/map":
            outtxt.write(str.format("{0:.9f} ", t.to_sec()))
            outtxt.write(str.format("{0:.9f} ", msg.pose.position.x))
            outtxt.write(str.format("{0:.9f} ", msg.pose.position.y))
            outtxt.write(str.format("{0:.9f} ", msg.pose.position.z))
            outtxt.write(str.format("{0:.9f} ", msg.pose.orientation.x))
            outtxt.write(str.format("{0:.9f} ", msg.pose.orientation.y))
            outtxt.write(str.format("{0:.9f} ", msg.pose.orientation.z))
            outtxt.write(str.format("{0:.9f}\n", msg.pose.orientation.w))