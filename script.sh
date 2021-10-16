# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    script.sh                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/16 13:13:33 by aihya             #+#    #+#              #
#    Updated: 2021/10/16 15:20:09 by aihya            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

while [ 1 ]
do
	osascript << EOF
		tell application "System Events"
    		tell every desktop
        		set picture to "$@"
    		end tell
		end tell
EOF
sleep 10
done
