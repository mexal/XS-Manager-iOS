//
//  MasterViewController.swift
//  XS-Manager
//
//  Created by Ivan Kravchenko on 15/07/14.
//  Copyright (c) 2014 DORMA. All rights reserved.
//

import UIKit

class MasterViewController: UITableViewController {
    
    var detailViewController: DetailViewController? = nil


    override func awakeFromNib() {
        super.awakeFromNib()
        if UIDevice.currentDevice().userInterfaceIdiom == .Pad {
            self.clearsSelectionOnViewWillAppear = false
            self.preferredContentSize = CGSize(width: 320.0, height: 600.0)
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        if let split = self.splitViewController {
            let controllers = split.viewControllers
            self.detailViewController = controllers[controllers.count-1].topViewController as? DetailViewController
        }
    }

    override func prepareForSegue(segue: UIStoryboardSegue!, sender: AnyObject!) {
        switch segue.identifier as String {
        case "showUART":
            println(segue.identifier)
        case "showPersons":
            ((segue.destinationViewController as UINavigationController).topViewController as DetailViewController).mode = DetailViewController.ContentMode.Persons
            println(segue.identifier)
        case "showDoors":
            ((segue.destinationViewController as UINavigationController).topViewController as DetailViewController).mode = DetailViewController.ContentMode.Doors
            println(segue.identifier)
        case "showPermissions":
            ((segue.destinationViewController as UINavigationController).topViewController as DetailViewController).mode = DetailViewController.ContentMode.Permissions
            println(segue.identifier)
        default:
            println("Segue is not defined")
        }
    }
}

